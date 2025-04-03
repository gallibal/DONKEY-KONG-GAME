#include "Mario.h"
#include "general.h"
#include <iostream>
#include <Windows.h>
#include "Board.h"
#include <conio.h>
#include "Game.h"

//------------------------------------------------------------------------------------------------------------------------------------
// Handles key presses to set Mario's direction or action
// Parameters:
// - key: The key pressed by the player
void Mario::keyPressed(char key)
{
	if (isJump || FloorFallingCounter > 0) return; // Ignore input if Mario is jumping or falling

	// Save the previous direction
	if (getdiffX() == 0)
		PrevDir.y = getdiffY();
	else
		PrevDir = { getdiffX(), getdiffY() };

	// Update Mario's direction based on the key pressed
	if (tolower(key) == LEFT)
		setdiffPos(-1, 0);
	else if (tolower(key) == UP)
		setdiffPos(0, -1);
	else if (tolower(key) == RIGHT)
		setdiffPos(1, 0);
	else if (tolower(key) == STAY)
		setdiffPos(0, 0);
	else if (tolower(key) == DOWN)
		setdiffPos(0, 1);

}
//------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------
// Moves Mario according to the current direction and game rules
void Mario::move()
{
	if (!isClimbingDownLadder())
	{
		if (getBoard()->getPosition(getX() + getdiffX(), getY()) == FLOOR)
			stopMovement();
		else if (getBoard()->getPosition(getX() + getdiffX(), getY()) == LEFT_SLOPE)
			stopMovement();
		else if (getBoard()->getPosition(getX() + getdiffX(), getY()) == RIGHT_SLOPE)
			stopMovement();
	}
	if (isJump == true)
	{
		jumping();
		return;
	}

	erase();


	//********** Prevent Mario from moving out of the game boundaries **********
	if (isOutOfBounds()) {
		stopMovement();
	}
	//********** Handle movement in different directions **********
	// --------------------------------------------------LEFT---------------------------------------------------------------
	else if (getdiffX() == -1 && getdiffY() == 0)           // Move left
		moveLeft();

	// --------------------------------------------------RIGHT---------------------------------------------------------------
	else if (getdiffX() == 1 && getdiffY() == 0)            // Move right
		moveRight();
	// --------------------------------------------------UP---------------------------------------------------------------
	else if (getdiffX() == 0 && getdiffY() == -1)           // Move up
		moveUp();
	// --------------------------------------------------STAY---------------------------------------------------------------

	else if (getdiffX() == 0 && getdiffY() == 0)              // Stay ,Do nothing, just redraw
	{
		stopMovement();
	}

	// --------------------------------------------------DOWN---------------------------------------------------------------
	else if (getdiffX() == 0 && getdiffY() == 1)            // Move down
	{
		moveDown();
	}

	// --------------------------------------------------FALL---------------------------------------------------------------
	if (MarioPause == false)
	{
		if (handleFalling())
			return;
	}
	// --------------------------------------------------WIN---------------------------------------------------------------
	if ((getBoard()->getPosition(getX(), getY()) == WIN_CONDITION_CHAR))                  // Check if Mario reaches the win condition
	{
		getBoard()->SetWinStage();                                    // Mark game as won
		if (getBoard()->isSilentMode()==false)
		{
			clrscr();
			getBoard()->printLevelScreen();
		}
		
	}

	else if (tolower(getBoard()->getPosition(getX(), getY())) == HAMMER)
	{
		setHammer();
		getBoard()->MariowithHammer(true);
		getBoard()->BoardDelete(getX(), getY());
	}
	else if (getBoard()->getPosition(getX(), getY()) == SURPRISE)
	{
		getBoard()->UpdateScore(rand() % 200);
		getBoard()->BoardDelete(getX(), getY());
	}
	draw(MARIO);                                                  // Redraw Mario at his new position
}

//------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------------------------------------------
// Handles Mario's jumping logic

void Mario::jumping() {
	if (!isJump) return;                                      // If Mario is not in a jumping state, do nothing
	static JumpStage stage = JumpStage::JumpUpStage1;
	erase();
	if (MarioPause == false) {
		switch (stage) {
		case JumpStage::JumpUpStage1:                         // Jumping up, first stage
			setY(getY() - 1);
			setX(getX() + PrevDir.x);
			stage = JumpStage::JumpUpStage2;
			break;

		case JumpStage::JumpUpStage2:                         // Jumping up, second stage
			setY(getY() - 1);
			setX(getX() + PrevDir.x);

			if (isJumpToNewStage())
			{
				stage = JumpStage::JumpUpStage1;
				isJump = false;
				setdiffY(0);
				setdiffX(PrevDir.x);
			}
			else {
				stage = JumpStage::FallDownStage1;
			}

			break;

		case JumpStage::FallDownStage1:                      // Falling down, first stage
			setY(getY() + 1);
			setX(getX() + PrevDir.x);
			stage = JumpStage::FallDownStage2;
			if (isJumpToNewStage())
			{
				stage = JumpStage::JumpUpStage1;
				isJump = false;
				setdiffY(0);
				setdiffX(PrevDir.x);
			}
			break;

		case JumpStage::FallDownStage2:                     // Falling down, second stage
			setY(getY() + 1);
			setX(getX() + PrevDir.x);
			if (isJumpToNewStage()) 
			{
				setdiffY(0);
				setdiffX(PrevDir.x);
			}
			stage = JumpStage::JumpUpStage1;                // Reset jump stage
			isJump = false;                                 // End jumping state
			setdiffPos(PrevDir.x, PrevDir.y);
			break;
		}

	}
	draw(MARIO);
}




bool Mario::isOutOfBounds() const {
	return ((getBoard()->getPosition(getX() + getdiffX(), getY() + getdiffY()) == BARRIER && getdiffY() != 1) ||
		(getBoard()->getPosition(getX() + getdiffX(), getY() + getdiffY()) == DONKEY_KONG) ||
		(getX() + getdiffX() == 0 || getX() + getdiffX() == GAME_WIDTH || getY() >= GAME_HEIGHT));
}


void Mario::stopMovement() {
	setdiffPos(0, 0);
	PrevDir.x = 0;

}

void Mario::moveLeft() {

	setX(getX() + getdiffX());
}

void Mario::moveRight() {

	setX(getX() + getdiffX());
}


void Mario::moveUp()
{
	if (getBoard()->getPosition(getX(), getY()) == LADDER)
	{ // Climbing a ladder
		setY(getY() + getdiffY());
	}
	else if (isOnFloor())
	{
		setX(getX() + getdiffX());
		setY(getY() + getdiffY());
		stopMovement();
	}
	else if ((getBoard()->getPosition(getX(), getY() + 1) == LADDER))
	{
		PrevDir.y = 0;
		PrevDir.x = 0;
		setdiffPos(0, 0);
	}
	else
	{
		if (canJump())
		{
			jumping();

		}
	}
}

bool Mario::isOnFloor() const
{
	return (getBoard()->getPosition(getX(), getY()) == FLOOR || getBoard()->getPosition(getX(), getY()) == LEFT_SLOPE || getBoard()->getPosition(getX(), getY()) == RIGHT_SLOPE);
}


// Checks if Mario can jump
bool Mario::canJump() {
	isJump = true;                   // Set the jumping state to true

	if (isJumpBlocked())
	{
		isJump = false;
		if (getX() + PrevDir.x != GAME_WIDTH && getX() + PrevDir.x != 0)
		{
			setX(getX() + PrevDir.x);
		}
		setdiffPos(PrevDir.x, PrevDir.y);
		return false;               // Jump is blocked
	}


	return true;                   // Jump is valid
}

bool Mario::isClimbingDownLadder() const
{

	return ((getBoard()->getPosition(getX(), getY() + 2) == LADDER) || (getBoard()->getPosition(getX(), getY() + 1) == LADDER));
}
bool Mario::isNearFloor() const
{
	// Check if Mario will land on a floor or boundary
	char below = getBoard()->getPosition(getX(), getY() + 1);
	return ((below == FLOOR) || (below == LEFT_SLOPE) || (below == RIGHT_SLOPE) || (below == BARRIER) || (getY() + 1 == GAME_HEIGHT));
}

void Mario::moveDown()
{
	if (isClimbingDownLadder())
	{
		setY(getY() + getdiffY());
		if (isNearFloor())
		{
			stopMovement();
		}
	}
	else
	{
		continuePreviousDirection();
	}
}

void Mario::continuePreviousDirection()
{

	if (getX() + getdiffX() != GAME_WIDTH && getX() + getdiffX() != 0)
	{
		if (getX() + PrevDir.x != GAME_WIDTH && getX() + PrevDir.x != 0)
		{
			setX(getX() + PrevDir.x);

		}
		setdiffPos(PrevDir.x, 0);

	}
	else
	{
		// Stop movement if a boundary exists
		setdiffPos(0, 0);
	}
}


bool Mario::handleFalling()
{
	// Check if Mario is above empty space and not jumping
	if (getBoard()->getPosition(getX(), getY() + 1) == SPACE && !isJump && getY() + 1 != GAME_HEIGHT) {
		setdiffX(0);                   // Stop horizontal movement
		setY(getY() + 1);              // Move Mario down
		FloorFallingCounter++;         // Increment falling counter
		PrevDir.x = 0;                 // Reset previous direction
	}

	// Check if Mario lands on a floor
	if (isNearFloor())
	{
		if (FloorFallingCounter >= MAX_MARIO_FALLING_POSSIBLE) { // If Mario falls too far, he dies
			getBoard()->deathreason(FALLING);                    // Set death reason to falling
			setdiefromfall();                                    // Mark Mario as dead
			FloorFallingCounter = 0;                             // Reset falling counter
			return true;                                         // Indicate Mario has died
		}
		else
		{
			FloorFallingCounter = 0;                             // Reset falling counter if Mario lands safely
		}
	}

	return false; // Mario is still alive
}




bool Mario::isJumpBlocked() const {
	const char BARRIERS[] = { RIGHT_SLOPE, LEFT_SLOPE, FLOOR, BARRIER }; // Characters representing barriers
	for (char barrier : BARRIERS) {
		if (getBoard()->getPosition(getX() + (2 * PrevDir.x), getY() - 2) == barrier ||
			getBoard()->getPosition(getX() + PrevDir.x, getY() - 1) == barrier ||
			getY() - 2 <= 0 ||
			(getX() + (2 * PrevDir.x)) >= GAME_WIDTH || (getX() + (2 * PrevDir.x)) <= 0 ||
			(getX() + (3 * PrevDir.x)) >= GAME_WIDTH || (getX() + (3 * PrevDir.x)) <= 0 ||
			(getX() + (4 * PrevDir.x)) >= GAME_WIDTH || (getX() + (4 * PrevDir.x)) <= 0 ||
			(getX() + PrevDir.x) >= GAME_WIDTH || (getX() + PrevDir.x) <= 0)



			
		{
			return true; // Jump is blocked

		}
	}
	return false; // Jump is not blocked
}
bool Mario::isJumpToNewStage() const
{
	char belowCurrent = getBoard()->getPosition(getX(), getY() + 1);
	char belowNext = getBoard()->getPosition(getX() + PrevDir.x, getY() + 1);

	return ((belowCurrent == FLOOR || belowCurrent == LEFT_SLOPE || belowCurrent == RIGHT_SLOPE || belowCurrent == BARRIER) ||
		(belowNext == FLOOR || belowNext == LEFT_SLOPE || belowNext == RIGHT_SLOPE || belowNext == BARRIER));
}