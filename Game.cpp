#include <iostream>
#include <conio.h>
#include "Game.h"
#include <filesystem>
#include <vector>
#include <string>
#include <windows.h>
#include <algorithm>


using namespace std;




//-------------------------------------------------------------------------------------------------------------


void Game::printscreen(char screen[GAME_HEIGHT][GAME_WIDTH]) const
{

	for (int i = 0; i < GAME_HEIGHT - 1; i++) {
		cout << screen[i] << '\n';
	}
	cout << screen[GAME_HEIGHT - 1];

}

//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------

int Game::selectLevel(const std::vector<std::string>& fileNames) const {
	clrscr();
	cout << "Available Levels:\n\n";

	for (size_t i = 0; i < fileNames.size(); ++i)
	{
		cout << i + 1 << ". " << fileNames[i] << '\n';
	}

	cout << "\nEnter the number of the level to start (1-" << fileNames.size() << "), or 0 to return to the menu:\n ";
	char choice;

	char ch = _getch();   
	choice = ch - '0';

	while (choice < 0 || choice > static_cast<int>(fileNames.size()))
	{
		gotoxy(60, 23);
		cout << "Invalid choice.";
		Sleep(500);
		gotoxy(60, 23);
		cout << "               ";
		ch = _getch();   
		choice = ch - '0';
	}
	return choice; 
}
//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------


void Game::PlayLevel(vector<string>& filenames, int startLevel)
{
	int mario_lives = 3;
	bool win = false;
	if (filenames.size() == 0)
	{
		clrscr();
		cout << "No board files found in the current directory.";
		cout << "\n\nPress any key to continue...";
		_getch();
		return;
	}
	if (isSave)
	{
		resetSaveFiles(filenames);
	}


	for (int i = startLevel - 1; i < filenames.size(); i++)
	{

		std::string filename_prefix = filenames[i].substr(0, filenames[i].find_last_of('.'));
		std::string stepsFilename = filename_prefix + ".steps";
		std::string resultsFilename = filename_prefix + ".result";

		long random_seed;
		Steps steps;
		Results results;	

		Board b;
		ShowConsoleCursor(false);
		if (b.loadBoard(filenames[i]))
		{
			b.ResetBoard();
			b.setBoardPos();
			if (b.getIsBoardValid())
			{
				Mario m(b.getMarioStartX(), b.getMarioStartY(), MARIO, &b, 0, 0);   // Initialize Mario

				Barrels BarrelsArray(b, b.getDKStartX(), b.getDKStartY());          // Initialize barrels manager
				m.SetLivesbyValue(mario_lives);

				Ghostim Ghosts(b, b.getGhostPos());                                 // Initialize Ghosts manager
				random_seed = static_cast<long>(std::chrono::system_clock::now().time_since_epoch().count());
				if(isSave)
					steps.setRandomSeed(random_seed);

				srand(random_seed);

				b.printBoard();                                                     // Print the board to the console
				b.setLegend();
				b.updateLivesDisplay(m.GetLives());                                 // Update the display of remaining lives
				int Arrival_Barrels_Time = 0;                                       // Timer for spawning barrels
				m.draw(MARIO);                                                      // Draw Mario on the start point
				bool GamePause = false;                                             // Tracks whether the game is paused
				bool MESSAGE = false;                                               // Tracks whether a pause message is displayed
				if (MainGameLoop(b, m, BarrelsArray, Ghosts,steps,results))
				{
					if (isSave)
					{
						steps.saveSteps(stepsFilename);
						results.saveResults(resultsFilename);
					}
					b.UpdateScore(RESET_SCORE);
					return;
				}
				else
				{
					win = true;
					if (isSave)
					{
						steps.saveSteps(stepsFilename);
						results.saveResults(resultsFilename);
					}

				}

				mario_lives = m.GetLives();

			}
			else
			{
				cout << "\nInvalid board file: " << filenames[i];
				cout << "\n\nPress any key to continue...";
				_getch();

			}
			if (i == filenames.size() - 1 && win)
			{
				b.printwinscreen();
				b.UpdateScore(RESET_SCORE);
			}

		}
		else
		{
			clrscr();
			cout << "Error opening file: " << filenames[i] << endl;
			cout << "\n\nPress any key to continue...";
			_getch();		
		}

	}

}

//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------


bool Game::MainGameLoop(Board& b, Mario& m, Barrels& BarrelsArray, Ghostim& Ghosts,Steps& steps, Results& results)
{
	

	clearBuffer();
	size_t iteration = 0;
	bool GamePause = false;

	while (!b.GetStagewin())
	{
		if (_kbhit())
		{
			char key = _getch();
			bool HammerUsed = false;
			if (key == ESC)                      // Handle pause functionality
			{
				GamePause = !GamePause;
				
			};
			if (GamePause == true && key == EXIT) // Handle exiting to the menu		
			{  
				
				return true;
				
			}
			if (tolower(key) == HAMMER && m.withHammer())
			{
				UseHammer(b, m, BarrelsArray, Ghosts);
				HammerUsed = true;
			}
			if (!GamePause) // Handle movement and clearing the pause message
			{
				m.keyPressed(key);
			}
			if (checkKey(key))
				steps.addStep(iteration, key);
			if (_kbhit())
			{
				char key2 = _getch();
				if (tolower(key2) == HAMMER && m.withHammer() && !HammerUsed)
				{
					steps.addStep(iteration, key2);
					UseHammer(b, m, BarrelsArray, Ghosts);
				}
			}
		}
		//----------------------------------------
		// Handle pause state for barrels and Mario
		if (GamePause == true)  //Puase
		{
			BarrelsArray.setStop();
			m.setStopMario();
			Ghosts.setStop();
		}
		else //Resume
		{
			BarrelsArray.RemoveStop();
			m.RemoveStopMario();
			Ghosts.RemoveStop();
		}if (!GamePause)
		{
			if (m.GetLives() == 0)                            // Check for game over or win conditions
			{
				return true;
			}
			if (iteration % 20 == 0 ) // Spawn the barrels in an allotted time
			{
				BarrelsArray.activateNext();
			}
		
			if (BarrelsArray.moveAll(m) || Ghosts.MoveAll(m))
			{
				results.addResult(iteration, Results::MarioLostLive, b.UpdateScore(GET_SCORE));
				ResetLvl(b, m, BarrelsArray, Ghosts);
			}
			
			
			m.move();
			if (iteration % 10 == 0)
			b.UpdateScore(SCORE_PER_LOOP);
			
			if (m.GetLives() == 0)                           // Handle game over
			{
				return true;
			}
			
			iteration++;                                // Increment the timer for barrels each loop
			Sleep(150);
		}
	}
	results.addResult(iteration, Results::finished,b.UpdateScore(GET_SCORE));
	return false;
}

//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------


void Game::Run() {
	std::vector<std::string> fileNames;

	getAllBoardFileNames(fileNames);

	while (true)
	{
		clrscr();
		printscreen(startscreen);
		ShowConsoleCursor(false);
		clearBuffer();
		char choice;
		choice = _getch();              // Get the user's choice from the menu

		if (choice == START_GAME)
		{
			PlayLevel(fileNames, 1);
		}
		else if (choice == CHOOSE_SCREEN)
		{
			int levelChoise = selectLevel(fileNames);
			if (levelChoise != 0)
				PlayLevel(fileNames, levelChoise);
		}
		else if (choice == INSTRUCTIONS)
		{
			clrscr();
			printscreen(instructions);
			choice = _getch();
			clrscr();
		}
		else if (choice == EXIT)
		{
			clrscr();
			printscreen(endscreen);
			gotoxy(1, 20);
			break;
		}
		else
		{
			gotoxy(1, 23);
			cout << "invalid char";
			Sleep(500);
			clrscr();
		}
	}
}


//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------


void Game::clearBuffer()
{
	while (_kbhit())
	{
		char dispose = _getch();
	}
}

bool Game::checkKey(char key)
{
	key = tolower(key);
	if (key == UP || key == DOWN || key == LEFT || key == RIGHT || key == STAY || key == HAMMER)
		return true;
	else
		return false;
}


void Game::resetSaveFiles(const std::vector<std::string>& filenames) {
		for (int i = 0; i < filenames.size(); i++) 
		{
			std::string filename_prefix = filenames[i].substr(0, filenames[i].find_last_of('.'));
			std::string stepsFilename = filename_prefix + ".steps";
			std::string resultsFilename = filename_prefix + ".result";

			std::ofstream resetFile(stepsFilename, std::ios::trunc); 
			resetFile.close(); 
			std::ofstream resetFile2(resultsFilename, std::ios::trunc); 
			resetFile2.close(); 
		}	
}