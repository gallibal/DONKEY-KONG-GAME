#ifndef  __MARIO_H
#define __MARIO_H

#include <iostream>
#include "general.h"
#include "Board.h"
#include "GameObject.h"



// Mario class represents the player's character in the game.
// It manages Mario's movement, jumping, falling, and interactions with the game board.
class Mario :public GameObject
{

	GameObject mario;
	struct Direction { int x, y; };           // Direction struct used to represent movement directions

	enum class JumpStage {
		JumpUpStage1,
		JumpUpStage2,
		FallDownStage1,
		FallDownStage2

	};
	Direction PrevDir{ 0,0 };                // Previous movement direction of Mario
	//int jumpStage = 0;                     // Tracks the current stage of a jump
	int FloorFallingCounter = 0;             // Counter for how long Mario has been falling from a floor
	bool isJump = false;                     // Indicates if Mario is in a jumping state
	bool isFalling = false;                  // Indicates if Mario is currently falling
	bool MarioPause = false;                 // Indicates if game is paused
	bool diefromfall = false;                // Indicates if Mario has died from falling
	bool CollectHammer = false;			     // Indicates if Mario has collected a hammer
	int lives = 3;


	Mario& operator=(const Mario&) = delete;


public:
	// Constructor: Initializes Mario's position
	Mario(int x, int y, char _symbol, Board* _b, int _diffx, int _ydiff = 0) : GameObject(x, y, _symbol, _b, _diffx, _ydiff) {}

	void jumping();                        // Handle Mario's jumping logic

	void keyPressed(char key);             // Handle key presses for Mario's movement

	void move();                           // Move Mario based on his current direction

	void setdiefromfall() { diefromfall = true; }             // Set Mario's state to indicate he died from falling

	void downdiefromfall() { diefromfall = false; }           // Reset Mario's state after falling

	bool isdiefromfall() const { return diefromfall; }         // Check if Mario has died from falling

	void reset(int _x, int _y)                                 // Reset Mario's position and state
	{
		setPos(_x, _y);
		setdiffPos(0, 0);
		CollectHammer = false;
		getBoard()->MariowithHammer(false);
	}

	void setStopMario()                                        // Stop Mario's movement
	{
		if (MarioPause == false)
			MarioPause = true;
	}
	void RemoveStopMario()                                    // Resume Mario's movement
	{
		MarioPause = false;
	}

	int GetLives() const { return lives; }                    // Get for the number of lives remaining

	void SetLives() { lives--; }                              // Decrement the number of lives

	void MarioCurrenetLivesUpdate(int CuurentMariolives) { lives = CuurentMariolives; }

	void setHammer() { CollectHammer = true; }               // Set Mario's state to indicate he has collected a hammer

	bool withHammer() const{ return CollectHammer; }         // Check if Mario has collected a hammer

	bool isOutOfBounds() const;                              // Check if Mario is out of the game boundaries

	void stopMovement();

	void moveLeft();

	void moveRight();

	void moveUp();

	void moveDown();

	bool isOnFloor() const;

	bool canJump();                                          // Check if Mario can jump

	bool isClimbingDownLadder() const;

	bool isNearFloor() const;

	void continuePreviousDirection();

	bool handleFalling();

	bool isJumpBlocked() const;                              // Check if Mario's jump is blocked

	void SetLivesbyValue(int _lives) { lives = _lives; }     // Update Mario's number of lives to a specific value

	bool isJumpToNewStage() const;                           // Check if Mario's jump reaches a new stage

};
#endif