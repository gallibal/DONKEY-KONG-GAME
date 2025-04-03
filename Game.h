#ifndef __GAME_H
#define __GAME_H


#include "GeneralMarioGame.h"
using namespace std;

// The Game class manages the entire game flow, including:
// - Starting the game
// - Displaying menus, instructions, and end screens
// - Running the main game loop

class Game : public GenralMarioGame
{
	char startscreen[GAME_HEIGHT][GAME_WIDTH] = {
	"===============================================================================",
	"=========       =====    ====  =======  ==  ====  ==        ==  ====  =========",
	"=========  ====  ===  ==  ===   ======  ==  ===  ===  ========   ==   =========",
	"=========  ====  ==  ====  ==    =====  ==  ==  ====  =========  ==  ==========",
	"=========  ====  ==  ====  ==  ==  ===  ==  =  =====  =========  ==  ==========",
	"=========  ====  ==  ====  ==  ===  ==  ==     =====      ======    ===========",
	"=========  ====  ==  ====  ==  ====  =  ==  ==  ====  ===========  ============",
	"=========  ====  ==  ====  ==  =====    ==  ===  ===  ===========  ============",
	"=========  ====  ===  ==  ===  ======   ==  ====  ==  ===========  ============",
	"=========       =====    ====  =======  ==  ====  ==        =====  ============",
	"===============================================================================",
	"=========  ====  ====    ====  =======  ===      ==============================",
	"=========  ===  ====  ==  ===   ======  ==   ==   =============================",
	"=========  ==  ====  ====  ==    =====  ==  ====  =============================",
	"=========  =  =====  ====  ==  ==  ===  ==  ===================================",
	"=========     =====  ====  ==  ===  ==  ==  ===================================",
	"=========  ==  ====  ====  ==  ====  =  ==  ===   =============================",
	"=========  ===  ===  ====  ==  =====    ==  ====  =============================",
	"=========  ====  ===  ==  ===  ======   ==   ==   =============================",
	"=========  ====  ====    ====  =======  ===      ==============================",
	"===============================================================================",
	"                          START GAME   - PRESS 1                               ",
	"                          SELECT LEVEL - PRESS 2                               ",
	"                          INSTRUCTIONS - PRESS 8                               ",
	"                          EXIT         - PRESS 9                               ",
	};

	char instructions[GAME_HEIGHT][GAME_WIDTH] = {

		"INSTRUCTIONS:                                                                  ",
		"UP         - PRESS w                                                           ",
		"LEFT       - PRESS a                                                           ",
		"STAY       - PRESS s                                                           ",
		"RIGHT      - PRESS d                                                           ",
		"DOWN       - PRESS x                                                           ",
		"USE HAMMER - PRESS p                                                           ",
		"PAUSE GAME - PRESS Esc                                                         ",
		"                         *TO WIN YOU NEED TO GET PAULINE ($)                   ",
		"                         *BE CAREFUL FROM THE BARRELS (O) AND GHOSTS (x)       ",
		"                         *YOU HAVE 3 LIVES                                     ",
		"                         *JUMP TAKE YOU 2 CHARS UP AND 4 HORIZONTAL            ",
		"                         *IF YOU DONT HAVE ENOUGH ROOM TO JUMP, THE            ",
		"                         JUMP WILL BE NOT POSSIBLE.                            ",
		"                         *TO GET A HAMMER GO TO 'p'                            ",
		"                         *RETURN THE MENU WHILE GAME - ESC AND AFTER 9         ",
		"                                                                               ",
		"######  ####### ####### ######     #       #     #  #####  #    #              ",
		"#       #     # #     # #     #    #       #     # #       #   #               ",
		"#       #     # #     # #     #    #       #     # #       #  #                ",
		"#  #### #     # #     # #     #    #       #     # #       ###                 ",
		"#     # #     # #     # #     #    #       #     # #       #  #                ",
		"#     # #     # #     # #     #    #       #     # #       #   #               ",
		"####### ####### ####### ######     #######  #####   #####  #    #              ",
		"    RETURN TO MENU  - PRESS ANY KEY                                            ",
	};

	char endscreen[GAME_HEIGHT][GAME_WIDTH] = {
	"                                                                               ",
	"                                                                               ",
	"                                                                               ",
	"                                                                               ",
	"                                                                               ",
	"                                                                               ",
	"          WE HOPE YOU ENJOY OUR GAME                                           ",
	"                                            WE WILL MISS YOU <3                ",
	"                                                                               ",
	"                                                                               ",
	"                                                                               ",
	"                                                                               ",
	"                                                                               ",
	"                                                                               ",
	"                                                                               ",
	"                                                                               ",
	"                                                                               ",
	"                                                                               ",
	"                                                                               ",
	"                                                                               ",
	"                                                                               ",
	"                                                                               ",
	"                                                                               ",
	"                                                                               ",
	"                                                                               ", };

	bool isSave; // Flag indicating whether to save game progress



public:

	Game(bool save) : isSave(save) {}

	void Run() override;                                                            // Starts the game by displaying menus and running the game loop

	~Game()  { ; }

	


	void printscreen(char screen[GAME_HEIGHT][GAME_WIDTH]) const;                   // Prints a specific screen (start, instructions, or end screen)

	int selectLevel(const std::vector<std::string>& fileNames) const;               // Displays the level selection menu and returns the user's choice

	bool MainGameLoop(Board& b, Mario& m, Barrels& BarrelsArray, Ghostim& Ghosts, Steps& steps, Results& results);

	void PlayLevel(vector<string>& filenames, int startLevel) override;                      // Manages the flow of playing through a level, including initialization and running the main game loop.


	void clearBuffer();                                                             // Clears the keyboard input buffer to remove any residual key presses.

	bool checkKey(char key);  //     Checks if a given key is valid for game control.

	void resetSaveFiles(const std::vector<std::string>& filenames);  //  Resets save files before starting a new game.


};

#endif