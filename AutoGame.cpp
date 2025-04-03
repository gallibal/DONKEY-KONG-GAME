#include "AutoGame.h"
#include <conio.h>
#include <cstdlib>
#include <filesystem>
#include <tuple>
using std::get;
using namespace std;

void AutoGame:: reportResultError(const std::string& message, const std::string& filename, size_t iteration) {
	system("cls");
	std::cout << "Screen " << filename << " - " << message << '\n';
	std::cout << "Iteration: " << iteration << '\n';
	std::cout << "Press any key to continue to next screens (if any)" << std::endl;
	_getch();
}

bool AutoGame::MainGameLoop(Board& b, Mario& m, Barrels& BarrelsArray, Ghostim& Ghosts, Steps& steps, Results& results)
{
	size_t iteration = 0;
	char step;
	size_t nextDieIteration = 0;
	while (!b.GetStagewin())
	{
		
		bool HammerUsed = false;
		if (steps.isNextStepOnIteration(iteration))
		{
			step = steps.popStep();
			if (step == HAMMER && m.withHammer())
			{
				UseHammer(b, m, BarrelsArray, Ghosts);
				HammerUsed = true;
			}
			else
			{
				m.keyPressed(step);
			}
			if (!steps.getSteps().empty())
			{
				if (steps.getSteps().front().first == iteration && steps.getSteps().front().second == HAMMER && !HammerUsed)
				{
					steps.popStep();
					UseHammer(b, m, BarrelsArray, Ghosts);
				}
			}
		}

		if (m.GetLives() == 0)
		{
			return true;
		}
		if (results.isFinishedBy(iteration) && isSilent)
		{
			unmatchingResultsFound = true;
			reportResultError("Results file reached finish while game hadn't!", b.getBoardFileName(), iteration);
		
			return true;
		}
		else
			nextDieIteration = results.getNextBombIteration();

		if (iteration % 20 == 0) 
		{
			BarrelsArray.activateNext();
		}
		if (BarrelsArray.moveAll(m) || Ghosts.MoveAll(m))
		{

			if (results.popResult() != std::tuple{ iteration,Results::MarioLostLive, b.UpdateScore(GET_SCORE) } && isSilent)
			{
				unmatchingResultsFound = true;
				reportResultError("Results file doesn't match die event!", b.getBoardFileName(), iteration);
				return true;
			}
			ResetLvl(b, m, BarrelsArray, Ghosts);
		}
		else
		{
			if (iteration == nextDieIteration && isSilent)
			{
				unmatchingResultsFound = true;
				reportResultError("Results file has a die event that didn't happen!", b.getBoardFileName(), iteration);

				return true;
			}
		}

		m.move();

		if (iteration % 10 == 0)
			b.UpdateScore(SCORE_PER_LOOP);
		if (m.GetLives() == 0)
		{
			return true;
		}
		iteration++;
		
		 Sleep(isSilent ? 0 : 70 );
		
	}
	if (!unmatchingResultsFound)
	{    
		if (results.popResult() != std::tuple{ iteration,Results::finished,b.UpdateScore(GET_SCORE) } && isSilent)
		{
			unmatchingResultsFound = true;
			reportResultError("Results file doesn't match finished event!", b.getBoardFileName(), iteration);

			return true;
		}
		if (results.getResults().empty())
			return false;
		else
		{
			if (std::get<1>(results.getResults().back()) != Results::noResult && isSilent)
			{
				unmatchingResultsFound = true;
				reportResultError("Results file has additional events after finish event!", b.getBoardFileName(), iteration);
				return true;

			}
		}	
	}
	return false;
}

void AutoGame::PlayLevel(vector<string>& filenames, int startLevel)
{
	int mario_Lives = 3;
	bool win = false;
	if (filenames.size() == 0)
	{
		clrscr();
		cout << "No board files found in the current directory.";
		cout << "\n\nPress any key to continue...";
		_getch();
		return;
	}

	for (int i = startLevel - 1; i < filenames.size(); i++)
	{

		std::string filename_prefix = filenames[i].substr(0, filenames[i].find_last_of('.'));
		std::string stepsFilename = filename_prefix + ".steps";
		std::string resultsFilename = filename_prefix + ".result";

		long random_seed;
		Steps steps;
		Results results;

		bool stepsExist = std::filesystem::exists(stepsFilename);
		bool resultsExist = std::filesystem::exists(resultsFilename);



		if (!isSilent)
		{
			if (!stepsExist || std::filesystem::file_size(stepsFilename) == 0)
			{
				clrscr();
				cout << "Skipping level: " << filenames[i] << " (Missing steps file)" << endl;
				cout << "Press any key to continue..." << endl;
				_getch();
				continue;
			}


			if (!resultsExist || std::filesystem::file_size(resultsFilename) == 0)
			{
				clrscr();
				cout << "Warning: No result file found for " << filenames[i] << "." << endl;
				cout << "The level can be played, but it cannot be verified." << endl;
				cout << "Press any key to continue..." << endl;
				_getch();

			}
		}
		

		Board b;
		ShowConsoleCursor(false);
		if (b.loadBoard(filenames[i]))
		{
			b.setBoardFileName(filenames[i]);
			b.ResetBoard();
			b.setBoardPos();
			if (b.getIsBoardValid())
			{
				Mario m(b.getMarioStartX(), b.getMarioStartY(), MARIO, &b, 0, 0);   // Initialize Mario

				Barrels BarrelsArray(b, b.getDKStartX(), b.getDKStartY());          // Initialize barrels manager
				m.SetLivesbyValue(mario_Lives);

				Ghostim Ghosts(b, b.getGhostPos());
				steps = Steps::loadSteps(stepsFilename);
				random_seed = steps.getRandomSeed();
				results = Results::loadResults(resultsFilename);// Initialize Ghosts manager
				srand(random_seed);
				b.setisSilent(isSilent);
				if (!isSilent)
				{
					b.printBoard();
					b.setLegend();

					b.updateLivesDisplay(m.GetLives());                                 // Update the display of remaining lives

					m.draw(MARIO);                                                      // Draw Mario on the start point

				}
			
				
				
				
				if (MainGameLoop(b, m, BarrelsArray, Ghosts, steps, results))
				{
					//if (!isSilent)
					b.UpdateScore(RESET_SCORE);

					if (unmatchingResultsFound == true)
					{
						//mario_Lives = m.GetLives();
						continue;
					}
					else
						return;

				}
				else
				{
					win = true;
				}
				mario_Lives = m.GetLives();

			}
			else
			{
				cout << "\nInvalid board file: " << filenames[i];
				cout << "\n\nPress any key to continue...";
				_getch();
			}
			if (i == filenames.size() - 1 && win)
			{
				if (!isSilent)
				{
					b.printwinscreen();
				}
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
	
};

void AutoGame::Run()
{
		std::vector<std::string> fileNames;
		getAllBoardFileNames(fileNames);
		ShowConsoleCursor(false);
			PlayLevel(fileNames, 1);
			if (unmatchingResultsFound == false && isSilent)
			{
				clrscr();
				cout << "TEST PASSED";

			}
		gotoxy(1, 20);
}