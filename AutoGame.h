#pragma once
#include "GeneralMarioGame.h"


 //--------------------------------------------------------------------------------------------
 //                AutoGame - Automatic game execution, supports silent mode.
 //--------------------------------------------------------------------------------------------
class AutoGame : public GenralMarioGame
{
	bool isSilent;  // Silent mode flag
	bool unmatchingResultsFound = false;  // Flag for mismatched results
public:
	AutoGame(bool _silent) :isSilent(_silent) { }
	
	~AutoGame()  { ; }


	//~AutoGame();
	void Run() override;
	bool MainGameLoop(Board& b, Mario& m, Barrels& BarrelsArray, Ghostim& Ghosts, Steps& steps, Results& results) override;  // Main game loop that controls the gameplay for a single level.

	void PlayLevel(vector<string>& filenames, int startLevel) override;   // Manages the flow of playing through a level, including initialization and running the main game loop.

	void reportResultError(const std::string& message, const std::string& filename, size_t iteration);  // Logs result errors
	
	void setisSilent(bool s) { isSilent = s; }
};

