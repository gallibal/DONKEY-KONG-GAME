#ifndef __GENERALMARIOGAME_H
#define __GENERALMARIOGAME_H

#include "Mario.h"
#include "Barrels.h"
#include "Ghostim.h"
#include "Steps.h"
#include "Results.h"

//------------------------------------------------------------------------------
// * GenralMarioGame - Abstract class for managing Mario game logic.
//------------------------------------------------------------------------------

class GenralMarioGame
{
 
 public: 
	virtual void Run() = 0;                             

	
	
	virtual ~GenralMarioGame() { ; }

	 void getAllBoardFileNames(std::vector<std::string>& vec_to_fill)  const ;        // Gets all the board file names from the current directory

	virtual bool MainGameLoop(Board& b, Mario& m, Barrels& BarrelsArray, Ghostim& Ghosts, Steps& steps, Results& results)=0;  // Main game loop that controls the gameplay for a single level.

	virtual void PlayLevel(vector<string>& filenames, int startLevel) = 0;                      // Manages the flow of playing through a level, including initialization and running the main game loop.

    void UseHammer(Board& b, Mario& m, Barrels& BarrelsArray, Ghostim& Ghosts);     // Handles the logic when Mario uses a hammer to attack barrels or ghosts.

    void ResetLvl(Board& b, Mario& m, Barrels& BarrelsArray, Ghostim& Ghosts);      // Resets the current level after Mario loses a life. Resets positions of Mario, barrels, and ghosts.

};
#endif
