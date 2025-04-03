#include "Board.h"
#include <cstring>
#include <iostream>
#include <string>
using namespace std;


//-------------------------------------------------------------------------------------------------------------
// Constructor: Initializes the board state
// Resets the board, sets lives to 3, and win state to false

Board::Board() {
	ResetBoard();
}
//-------------------------------------------------------------------------------------------------------------
// Resets the current board to match the original layout
void Board::ResetBoard() {
	for (size_t i = 0; i < GAME_HEIGHT; i++)
	{
		for (size_t j = 0; j < GAME_WIDTH + 1; j++)
		{
			currentBoard[i][j] = originalBoard[i][j];
		}
		currentBoard[i][GAME_WIDTH] = '\0';
	}
}
//-------------------------------------------------------------------------------------------------------------

void Board::printBoard() const {
	clrscr();
	for (size_t i = 0; i < GAME_HEIGHT - 1; i++) {
		cout << currentBoard[i] << '\n';
	}
	cout << currentBoard[GAME_HEIGHT - 1];
}


//-------------------------------------------------------------------------------------------------------------
// Updates the lives display at the top of the screen
// Uses hearts ("<3") to represent the remaining lives
void Board::updateLivesDisplay(int lives) 
{
	if (!isSilent)
	{
		if (lives == 2) {
			gotoxy(LegendPos.getX() + 12, LegendPos.getY());
			cout << "  ";
		}
		else if (lives == 1) {
			gotoxy(LegendPos.getX() + 9, LegendPos.getY());
			cout << "     ";
		}
		else if (lives == 0) {
			clrscr();
			for (int i = 0; i < 25; i++)
			{
				for (int j = 0; j < 80; j++)
					cout << losescreen[i][j];
				if (i != 24) cout << endl;
				Sleep(50);
			}
			Sleep(1000);
			clrscr();
		}
	}
}
//-------------------------------------------------------------------------------------------------------------
// Prints the win screen to the console
void Board::printwinscreen() const
{
	clrscr();
	for (int i = 0; i < GAME_HEIGHT - 1; i++) {
		cout << winscreen[i] << '\n';
		Sleep(50);
	}
	cout << winscreen[GAME_HEIGHT - 1];
	Sleep(1000);
}
void Board::printLevelScreen() const
{
		clrscr();
		for (int i = 0; i < GAME_HEIGHT - 1; i++) {
			cout << levelwinscreen[i] << '\n';
		}
		cout << levelwinscreen[GAME_HEIGHT - 1];
	Sleep(1000);
}
//-------------------------------------------------------------------------------------------------------------
// Displays the reason for Mario's death at the top of the screen
// Parameters:
//  reason: An integer indicating the cause of death (1 = fall, 2 = barrel hit, 3 = barrel explosion)

void Board::deathreason(int reason)
{
	gotoxy(LegendPos.getX(), LegendPos.getY() + 2);
	switch (reason)
	{
	case FALLING:
		cout << "Fall               ";
		break;
	case BARREL_HIT:
		cout << "Barrel hit         ";
		break;
	case BARREL_EXPLOSION:
		cout << "Barrel explosion   ";
		break;
	case GHOST_HIT:
		cout << "Ghost hit          ";
		break;
	case RESET_DEATH_REASON:
		cout << "                   ";
		break;
	}
}

//---------------------------------------------------------------------------------------------------------
// Loads a board layout from a file and initializes the board's `originalBoard` state.
bool Board::loadBoard(const string& fileName)
{
	int countRows = 0, len, i, j;
	string line;
	ifstream boardFile(fileName);

	if (boardFile.is_open())
	{
		while (std::getline(boardFile, line) && countRows < GAME_HEIGHT) {
			len = line.size();
			for (i = 0; i < GAME_WIDTH; i++) {
				if (i < len)
					originalBoard[countRows][i] = line[i];
				else
					originalBoard[countRows][i] = ' ';
			}
			originalBoard[countRows][i] = '\0';


			countRows++;
		}

		if (countRows < GAME_HEIGHT) {
			for (j = countRows; j < GAME_HEIGHT; j++) {
				for (i = 0; i < GAME_WIDTH + 1; i++)
					originalBoard[j][i] = ' ';
				originalBoard[j][i] = '\0';
			}
		}
	}
	else
	{
		return false;
	}
	boardFile.close();
	return true;
}
//---------------------------------------------------------------------------------------------------------
// Displays the legend (Lives and Score) on the game board.
// The legend is drawn starting from the position stored in `LegendPos`.
void Board::setLegend()
{

	gotoxy(LegendPos.getX(), LegendPos.getY());
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 20; j++)
			cout << Legend[i][j];
		gotoxy(LegendPos.getX(), LegendPos.getY() + i + 1);
	}
}

//---------------------------------------------------------------------------------------------------------
// Sets the initial positions of various objects on the board (e.g., Mario, Donkey Kong, Ghosts).
// Validates the board and checks that the required objects are correctly placed.
// If invalid placements are found (e.g., Pauline in the air), the board is marked as invalid.
void Board::setBoardPos()
{
	bool found = false;
	isBoardValid = true;

	int L_count = 0, MarioCount = 0, HammerCount = 0, PaulineCount = 0, ErrorCount = 0;
	clrscr();
	GhostPos.clear();


	for (int x = 0; x < GAME_WIDTH; x++)
	{
		for (int y = 0; y < GAME_HEIGHT; y++)
		{

			char ch = getPosition(x, y);
			switch (ch)
			{
			case MARIO:
			{
				setMarionStartPos(x, y);
				MarioCount++;
				BoardDelete(x, y);
				break;
			}
			case DONKEY_KONG:
			{
				setDKStartPos(x, y); // Set the starting position of Donkey Kong
				DonkeyCount++;

				break;
			}
			case WIN_CONDITION_CHAR: //Pauline
			{
				PaulineCount++;
				if (getPosition(x, y + 1) == SPACE && y + 1 != GAME_HEIGHT)
				{
					cout << "Pauline cannot be located in air\n ";
					setIsBoardValid(false);
				}
				break;

			}
			case HAMMER:
			{
				HammerCount++;
				break;
			}
			case LEGEND:
			{
				L_count++;
				setLegendPos(Point(x, y));
				BoardDelete(x, y);
				for (int i = y; i < y + 3; i++)
				{
					bool  isbreak = false;
					for (int j = x; j < x + 20; j++)
					{

						if (getPosition(x, y) != SPACE)
						{
							cout << "There is not enough space for L, it requires a 20x3 area.\n";
							setIsBoardValid(false);
							isbreak = true;
							break;
						}

					}
					if (isbreak)
						break;

				}
				break;
			}
			case GHOST_CHAR:
			{
				if (ch == GHOST_CHAR)
					GhostPos.emplace_back(Point(x, y), GHOST_CHAR);
				BoardDelete(x, y);
				if (getPosition(x, y + 1) == SPACE && y + 1 != GAME_HEIGHT)
				{
					cout << "Ghost cannot be located in air\n";
					setIsBoardValid(false);
				}
				break;
			}
			case CLIMB_GHOST:
				GhostPos.emplace_back(Point(x, y), CLIMB_GHOST);
				BoardDelete(x, y);
				if (getPosition(x, y + 1) == SPACE && y + 1 != GAME_HEIGHT)
				{
					cout << "Ghost cannot be located in air\n";
					setIsBoardValid(false);
				}
			case '>':
				break;
			case '<':
				break;
			case '=':
				break;
			case ' ':
				break;
			case 'Q':
				break;
			case 'H':
				break;
			default:
			{


				cout << "There are unrecognized characters on the screen : ";
				cout << ch << endl;
				setIsBoardValid(false);
				break;
			}
			}
		}
	}
	if (MarioCount != 1)
	{
		cout << "There is more or less than one Mario on the screen.\n";
		setIsBoardValid(false);
	}

	if (PaulineCount != 1)
	{

		cout << "There is more or less than one Pauline on the screen.\n";
		setIsBoardValid(false);

	}

	if (DonkeyCount > 1)
	{

		cout << "There is more than one Donkey Kong on the screen.\n";
		setIsBoardValid(false);

	}

	if (HammerCount > 1)
	{

		cout << "There is more than one Hammer on the screen.\n";

		setIsBoardValid(false);

	}
	if (L_count != 1)
	{
		cout << "L need to apear one time on the screen.\n";
		setIsBoardValid(false);
	}

	while (!found)
	{
		int x = rand() % GAME_WIDTH;
		int y = rand() % GAME_HEIGHT;
		if ((getPosition(x, y + 1) == FLOOR || getPosition(x, y + 1) == LEFT_SLOPE || getPosition(x, y + 1) == RIGHT_SLOPE || getPosition(x, y + 1) == BARRIER) && getPosition(x, y) == ' ')
		{
			Surprise(x, y);
			found = true;
		}
	}
}



int Board::UpdateScore(int addscore)
 {
	static int score = 0;
	if (addscore == GET_SCORE)
	{
		return score;
	}
	else
	{
		gotoxy(LegendPos.getX() + 7, LegendPos.getY() + 1);
		score += addscore;
		if (addscore == RESET_SCORE)
			score = 0;
		else if(!isSilent)
		  cout << score;
		return 0;
	}
}


void Board::MariowithHammer(bool g)
{
	gotoxy(LegendPos.getX() + 14, LegendPos.getY() + 1);
	if (g)
		cout << "P";
	else
		cout << " ";
}
