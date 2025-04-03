#ifndef  __GENERAL_H
#define __GENERAL_H
// ----------------------------------------------------
// Constants and Utility Functions for the Game
// ----------------------------------------------------

// Key definitions for game controls
static constexpr char START_GAME = '1';       // Key to start the game from the menu
static constexpr char CHOOSE_SCREEN = '2';    // Key to choose a specific screen from the menu
static constexpr char INSTRUCTIONS = '8';    // Key to display instructions from the menu
static constexpr char EXIT = '9';            // Key to exit the game
static constexpr int ESC = 27;               // Escape key for pausing and resuming the game
static constexpr int RESET_SCORE = 2;      // Key to reset the score
static constexpr int KILL_SCORE = 10;		// Score to be added when Mario kills a ghost or a barrel
static constexpr int SCORE_PER_LOOP = 1;	// Score to be added when loop of the game is completed
static constexpr int GET_SCORE = 3;	// Score to be added when loop of the game is completed
// death reasons
static constexpr int FALLING = 1;
static constexpr int BARREL_HIT = 2;
static constexpr int BARREL_EXPLOSION = 3;
static constexpr int GHOST_HIT = 4;
static constexpr int RESET_DEATH_REASON = 5;

// Dimensions of the game board
static constexpr int GAME_WIDTH = 80;        // Width of the game board in characters
static constexpr int GAME_HEIGHT = 25;       // Height of the game board in characters


// Array of valid movement keys for Mario
static constexpr char keys[] = { 'a', 'w', 'd', 'x', 's' }; // Movement keys: left, up, right, down, and stay
static constexpr size_t numKeys = sizeof(keys) / sizeof(keys[0]); // Number of valid keys


// Maximum number of barrels allowed in the game
static constexpr int MAX_BARRELS = 10; // Controls the upper limit of active barrels at any time
const int MAX_MARIO_FALLING_POSSIBLE = 5;

const char FLOOR = '=';
const char LEFT_SLOPE = '<';
const char RIGHT_SLOPE = '>';
const char BARRIER = 'Q';
const char LADDER = 'H';
const char WIN_CONDITION_CHAR = '$';
const char DONKEY_KONG = '&';
const char MARIO = '@';
const char GHOST_CHAR = 'x';
const char CLIMB_GHOST = 'X';

const char BARREL = 'O';
const char SPACE = ' ';
const char HAMMER = 'p';
const char LEGEND = 'L';
const char SURPRISE = '?';

const char UP = 'w';    
const char DOWN = 'x';  
const char LEFT = 'a';  
const char RIGHT = 'd'; 
const char STAY = 's';  




void gotoxy(int x, int y);
void clrscr();
void ShowConsoleCursor(bool showFlag);


#endif // ! __GENRAL_H