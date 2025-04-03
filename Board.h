#ifndef __BOARD_H
#define __BOARD_H
#include "general.h"
#include <iostream>
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#define byte win_byte 
#include "Windows.h"
#undef byte           
#include <fstream>
#include <vector>
#include "Point.h"

using namespace std;

// The Board class represents the game board and handles its state.
// It manages the layout, player lives, win/lose states, and displays.
class Board
{
    char originalBoard[GAME_HEIGHT][GAME_WIDTH + 1];
    char currentBoard[GAME_HEIGHT][GAME_WIDTH + 1];
    char winscreen[GAME_HEIGHT][GAME_WIDTH] = {
   "          $$\\     $$\\  $$$$$$\\    $$\\   $$\\                               ",
   "          \\$$\\   $$  |$$  __$$\\   $$ |  $$ |                                ",
   "           \\$$\\ $$  / $$ /  $$ |  $$ |  $$ |                                 ",
   "            \\$$$$  /  $$ |  $$ |  $$ |  $$ |                                  ",
   "             \\$$  /   $$ |  $$ |  $$ |  $$ |                                  ",
   "              $$ |    $$ |  $$ |  $$ |  $$ |                                   ",
   "              $$ |     $$$$$$  |  \\$$$$$$ |                                   ",
   "              \\__|    \\______/    \\______/                                  ",
   "                                                                               ",
   "                                                                               ",
   "                                                                               ",
   "          $$\\      $$\\    $$$$$$\\    $$\\   $$\\                            ",
   "          $$ | $\\  $$ |   \\_$$  _|   $$$\\  $$ |                             ",
   "          $$ |$$$\\ $$ |     $$ |     $$$$\\ $$ |                              ",
   "          $$ $$ $$\\$$ |     $$ |     $$ $$\\$$ |                              ",
   "          $$$$  _$$$$ |     $$ |     $$ \\$$$$ |                               ",
   "          $$$  / \\$$$ |     $$ |     $$ |\\$$$ |                              ",
   "          $$  /   \\$$ |   $$$$$$\\    $$ | \\$$ |                             ",
   "          \\__/     \\__|   \\______|    \\__|  \\__|                          ",
   "                                                                               ",
   "                                                                               ",
   "                                                                               ",
   "                                                                               ",
   "                                                                               ",
   "                                                                               ",
    };
    char losescreen[GAME_HEIGHT][GAME_WIDTH] = {
    "                $$$$$$\\   $$$$$$\\  $$\\      $$\\ $$$$$$$$\\                 ",
    "                $$  __$$\\ $$  __$$\\ $$$\\    $$$ |$$  _____|                 ",
    "                $$ /  \\__|$$ /  $$ |$$$$\\  $$$$ |$$ |                        ",
    "                $$ |$$$$\\ $$$$$$$$ |$$\\$$\\$$ $$ |$$$$$\\                    ",
    "                $$ |\\_$$ |$$  __$$ |$$ \\$$$  $$ |$$  __|                     ",
    "                $$ |  $$ |$$ |  $$ |$$ |\\$  /$$ |$$ |                         ",
    "                \\$$$$$$  |$$ |  $$ |$$ | \\_/ $$ |$$$$$$$$\\                  ",
    "                 \\______/ \\__|  \\__|\\__|     \\__|\\________|              ",
    "                                                                               ",
    "                                                                               ",
    "                                                                               ",
    "                 $$$$$$\\  $$\\    $$\\ $$$$$$$$\\ $$$$$$$\\                   ",
    "                $$  __$$\\ $$ |   $$ |$$  _____|$$  __$$\\                     ",
    "                $$ /  $$ |$$ |   $$ |$$ |      $$ |  $$ |                      ",
    "                $$ |  $$ |\\$$\\  $$  |$$$$$\\    $$$$$$$  |                   ",
    "                $$ |  $$ | \\$$\\$$  / $$  __|   $$  __$$<                     ",
    "                $$ |  $$ |  \\$$$  /  $$ |      $$ |  $$ |                     ",
    "                 $$$$$$  |   \\$  /   $$$$$$$$\\ $$ |  $$ |                    ",
    "                 \\______/     \\_/    \\________|\\__|  \\__|                 ",
    "                                                                               ",
    "                                                                               ",
    "                                                                               ",
    "                                                                               ",
    "                                                                               ",
    "                                                                               ",
    };

    char levelwinscreen[25][80] = {
    "                                                                               ",
    "| $$                                        $$                                 ",
    "| $$         $$$$     $$      $$| $$$$$$    $$                                 ",
    "| $$       $$    $$|   $$  /_$$| $$    $$| |$$                                 ",
    "| $$      | $$$$$$$$ \\  $$/|$$   $$$$$$$$|| $$                                ",
    "| $$      | $$_____/  \\  $$$/  | $$_____/|| $$                                ",
    "| $$$$$$$$|  $$$$$$$   \\  $/  |  $$$$$$$| | $$                          ",
    "|________/ \\_______/    \\_/    \\_______/ |__/                               ",
    "                                                                               ",
    "                                                                               ",
    "                                                                               ",
    "   $$$$$$                                                                      ",
    "  $$    $$                                        $$                           ",
    "| $$  \\__/   $$$$$$    $$$$$$$$$$$$$ | $$$$$$$$   $$     $$$$$    $$    $$$$$",
    "| $$        $$|   $$_ $$_  $$ __  $$|  $$ __  $$ |$$_   $$   $$   $$   $$ $$  ",
    "| $$      | $$  \\ $$| $$ \\\\$$|    $$ \\ $$     $$  $$  | $$$$$   $$$$$$ $$$$",
    "| $$    $$| $$  | $$| $$ | $$ |   $$|  $$  | $$|  $$    $$  _____/$$ | $$___",
    "|  $$$$$$/|  $$$$$$/| $$ | $$ |   $$|  $$$$$$$/|  $$    $$$$$$$   $$$$/|$$$$$",
    " \\______/  \\______/ |__/ |__/ |__/|    $$____/| __$$/ \\_______/ \\___/  \\___",
    "                                    |  $$                                     ",
    "                                    |  $$                                      ",
    "                                    |__/                                       "
    };



    bool StageDone = false;                                // Tracks if the current stage is complete
    Point MarioStartPos;                                   // Starting position of Mario
    Point DK_startPos;                                     // Starting position of Donkey Kong
    Point LegendPos;                                       // Position of the legend display
    bool isBoardValid = true;                              // Indicates if the board is valid
    int DonkeyCount = 0;                                   // Count of Donkey Kong instances on the board
    vector<pair<Point, char>> GhostPos;                                // Positions of Ghosts on the board
    string fileName = "";
    bool isSilent = false;
    char Legend[3][20] = {                                 // Legend display (e.g., Lives, Score)
    "Lives <3 <3 <3     ",
    "Score:             ",
    "                   "
    };

    // Disable copy constructor and assignment operator
    Board(const Board&) = delete;
    Board& operator=(const Board&) = delete;

public:
    // Constructor: Initializes the board state
    Board();

    void setisSilent(bool s) { isSilent = s; }

    void BoardDelete(int x, int y)
    {
        currentBoard[y][x] = ' ';
    }
    void Surprise(int x, int y)
    {
        currentBoard[y][x] = '?';
    }


    void printLevelScreen() const;

    void setBoardFileName(string& s)
    {
        fileName = s;
    }
    string getBoardFileName() const { return fileName; }
    

    void ResetBoard();                                         // Resets the board to its initial state

    void printBoard() const;                                   // Prints the current state of the board

    char getPosition(int x, int y) const {                     // Returns the character at a specific position on the board
        return currentBoard[y][x];                             // `y` is the row, `x` is the column 
    }
    void updateLivesDisplay(int lives);                       // Updates the lives display at the top of the screen

    void printwinscreen() const;                              // Prints the win screen to the console

    void deathreason(int reason);                            // Displays the reason for Mario's death

    bool loadBoard(const std::string& filename);

    void setBoardPos();                       // Set the starting positions of Mario, Donkey Kong, and Ghosts on the board and check if the board is valid

    void setMarionStartPos(int x, int y) { MarioStartPos.setX(x); MarioStartPos.setY(y); } // Set the starting position of Mario

    void setDKStartPos(int x, int y) { DK_startPos.setX(x); DK_startPos.setY(y); } // Set the starting position of DK

    // Get Mario's starting X coordinate
    int getMarioStartX() const { return MarioStartPos.getX(); }


    // Get Mario's starting Y coordinate
    int getMarioStartY() const { return MarioStartPos.getY(); }

    void MariowithHammer(bool g);

    // Get Donkey Kong's starting X coordinate
    int getDKStartX() const { return DK_startPos.getX(); }

    // Get Donkey Kong's starting Y coordinate
    int getDKStartY() const { return DK_startPos.getY(); }

    // Get Ghosts' positions
    vector<pair<Point, char>> getGhostPos() const { return GhostPos; }

    //void DeleteAllObjectsFromStart();

    void SetWinStage() { StageDone = true; }             // Set the win state to true

    bool GetStagewin()const { return StageDone; }        // Get for the win state

    void DownWinStage() { StageDone = false; }

    int getDonkeyCount() const { return DonkeyCount; }



    void setBoardPosition(int x, int y, char value) {
        currentBoard[y][x] = value;
    }

    void setIsBoardValid(bool s) { isBoardValid = s; }

    bool getIsBoardValid() const { return isBoardValid; }

    void setLegend();                                         // Sets the legend display on the board

    void setLegendPos(Point p) { LegendPos = p; }             // Sets the position of the legend

    int UpdateScore(int addscore);                           // Updates the player's score

    bool isSilentMode() const { return isSilent; }


};
#endif 