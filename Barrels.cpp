#include "Barrels.h"
#include <cstdlib> 
#include "Mario.h"


//---------------------------------------------------------------------------------------------------------------------------


void Barrels::reset() {
	for (int i = 0; i < barrels.size(); i++)
	{
		barrels[i].erase();
	}
	barrels.clear();
	lastDirections.clear();
}

//---------------------------------------------------------------------------------------------------------------------------
// Activates the next available barrel in the array
// This function finds the next inactive barrel and activates it. If all barrels are active, 
// it attempts to reuse an inactive barrel.
// Each activated barrel is reset to its initial state, assigned a random direction, and linked to the game board.


void Barrels::activateNext()
{
	if (bBoard->getDonkeyCount() == 0)
	{
		return;
	}
	else if (barrels.size() < MAX_BARRELS)
	{
		int direction = rand() % 2 == 0 ? 1 : -1;
		lastDirections.push_back(direction);
		barrels.push_back(Barrel(startPosX + direction, startPosY, BARREL , bBoard, direction, 0));
	}
}




//---------------------------------------------------------------------------------------------------------------------------
// Handles the movement and interaction of all active barrels
// Parameters:
// - mario: Reference to the Mario object for collision and death checks
// Returns:
// - true if Mario dies (from a barrel hit, explosion, or falling)
// - false if Mario survives this frame


bool Barrels::moveAll(Mario& mario)
{  
	if (mario.isdiefromfall())                                                   // Check if Mario has died from falling
	{
		mario.downdiefromfall();
		return true;
	}
	for (int i = 0; i < barrels.size(); i++)
	{
		
		if (Pause == true)                                                       // Check if the game is paused
			barrels[i].move(0, mario);
		else
		{		
			lastDirections[i] = barrels[i].move(lastDirections[i], mario);
			if (lastDirections[i] == 666)                                        // Check if the barrel hits Mario
			{
				bBoard->deathreason(BARREL_HIT);                                 // Death reason: Barrel hit
				return true;
			}
			if (barrels[i].Get_IsExploded())                                     // Check if the barrel has exploded
			{
				if (barrels[i].isMarioInRadius(mario.getX(), mario.getY(), 2))   // Check if Mario is within the explosion radius
				{
					bBoard->deathreason(BARREL_EXPLOSION);                       // Death reason : Barrel explosion
					return true;
				}
			}
			if (!barrels[i].Get_IsActive()) {
				removeBarrel(i);
			}					
		}
	}
	return false;
}

//---------------------------------------------------------------------------------------------------------------------------
// Checks if a barrel is located at the given coordinates (x, y). If found, removes the barrel and returns true.
// Returns:
// - true: If a barrel was found at the given location and removed- means that mario with hammer and kill him.
// - false: If no barrel was found at the given location.
bool Barrels::BarreldiefromHammer(int x, int y)
{
	for (int i = 0; i < barrels.size(); i++)
	{
		if (barrels[i].getX() == x && barrels[i].getY() == y)
		{	
			removeBarrel(i);
			return true;
		}
	}
	return false;
}
//-------------------------------------------------------------------------------------------------------------
// Removes a barrel from the list of barrels and updates the corresponding direction data.
void Barrels::removeBarrel(int i)                   // Removes a barrel from the array
{
	barrels.erase(barrels.begin() + i);
	lastDirections.erase(lastDirections.begin() + i);
}
