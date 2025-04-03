#include "GeneralMarioGame.h"
#include <iostream>
#include <conio.h>
#include <filesystem>
#include <vector>
#include <string>
#include <windows.h>
#include <algorithm>


void GenralMarioGame::getAllBoardFileNames(std::vector<std::string>& vec_to_fill)  const
// Gets all the board file names from the current directory
{
	namespace fs = std::filesystem;
	for (const auto& entry : fs::directory_iterator(fs::current_path())) {
		auto filename = entry.path().filename();
		auto filenameStr = filename.string();
		if (filenameStr.substr(0, 6) == "dkong_" && filename.extension() == ".screen") {
			vec_to_fill.push_back(filenameStr);
		}
	}
	sort(vec_to_fill.begin(), vec_to_fill.end());
}


void GenralMarioGame::UseHammer(Board& b, Mario& m, Barrels& BarrelsArray, Ghostim& Ghosts)
{
	if ((Ghosts.MarioKillGhost(m.getX() + m.getdiffX(), m.getY())) ||
		Ghosts.MarioKillGhost(m.getX() + 2 * m.getdiffX(), m.getY()))
	{
		b.UpdateScore(KILL_SCORE);
	}
	if (BarrelsArray.BarreldiefromHammer(m.getX() + m.getdiffX(), m.getY()) || BarrelsArray.BarreldiefromHammer(m.getX() + 2 * m.getdiffX(), m.getY()))// Handle the death of barrels from hammers
	{
		b.UpdateScore(KILL_SCORE);
	}

}


void GenralMarioGame::ResetLvl(Board& b, Mario& m, Barrels& BarrelsArray, Ghostim& Ghosts)
{
	
	m.draw(MARIO);
	if (b.isSilentMode() == false)
		Sleep(1500);
	b.deathreason(RESET_DEATH_REASON);				   // Erase the death reason
	m.erase();
	m.reset(b.getMarioStartX(), b.getMarioStartY());
	BarrelsArray.reset();			                   // Reset the barrels
	Ghosts.resetAll();
	Ghosts.setGhostPos(b.getGhostPos());
	m.SetLives();                                      // Decrement the number of Mario's lives
	b.updateLivesDisplay(m.GetLives());                // Update the display of remaining live
}