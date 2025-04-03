#include "Ghostim.h"
#include <vector>
#include <iostream>

void Ghostim::setGhostPos(vector<pair<Point, char>> pos) {
    for (int i = 0; i < pos.size(); i++) {
        if (pos[i].second == 'X') {
            GhostimArray.push_back(std::make_unique<ClimbGhost>(
                pos[i].first.getX(), pos[i].first.getY(), 'X', b, 1, 0));
        }
        else {
            GhostimArray.push_back(std::make_unique<BasicGhost>(
                pos[i].first.getX(), pos[i].first.getY(), 'x', b, 1, 0));
        }
        GhostimArray[i]->setStartPos(pos[i].first.getX(), pos[i].first.getY());
    }
}

void Ghostim::resetAll() {
    for (auto& ghost : GhostimArray) {
        ghost->erase();
    }
    GhostimArray.clear();
}

bool Ghostim::MarioKillGhost(int x, int y) {
    for (size_t i = 0; i < GhostimArray.size(); i++) {
        if (GhostimArray[i]->getX() == x && GhostimArray[i]->getY() == y) {
            GhostimArray[i]->erase();
            GhostimArray.erase(GhostimArray.begin() + i);
            return true;
        }
    }
    return false;
}

void Ghostim::isGhostsColliding(Ghost& CurrGhost) {
    int currX = CurrGhost.getX();
    int currY = CurrGhost.getY();
    int dirX = CurrGhost.getdiffX();

    vector<pair<Ghost*, int>> changes;

    for (auto& other : GhostimArray) {
        Ghost* otherPtr = other.get();
        if (&CurrGhost != otherPtr) {
            int otherX = other->getX();
            int otherY = other->getY();
            int otherDirX = other->getdiffX();
            static int PrevdirX = 0;

            if (dirX == 0) {
                CurrGhost.setdiffX(-PrevdirX);
            }
            if ((currX + dirX == otherX && currY == otherY) ||
                (otherX + otherDirX == currX && otherY == currY)) {
                if (dirX != otherDirX) {
                    changes.push_back({ &CurrGhost, -dirX });
                    changes.push_back({ otherPtr, -otherDirX });
                }
            }
            else if (currX + dirX == otherX + otherDirX && currY == otherY) {
                CurrGhost.setdiffX(0);
                PrevdirX = dirX;
            }
        }
    }

    for (auto& change : changes) {
        change.first->setdiffX(change.second);
        change.first->setChangeDirState();
    }
}

bool Ghostim::MoveAll(Mario& mario) {
    for (auto& ghost : GhostimArray) {
        if (ghost->getX() == mario.getX() && ghost->getY() == mario.getY()) {
            b->deathreason(GHOST_HIT);
            return true;
        }
    }

    for (auto& ghost : GhostimArray) {
        isGhostsColliding(*ghost);
    }

    for (auto& ghost : GhostimArray) {
        if (!Pause) {

            ghost->move();

        }
    }

    for (auto& ghost : GhostimArray) {
        ghost->setDownChangeDirState();
    }

    for (auto& ghost : GhostimArray) {
        if (ghost->getX() == mario.getX() && ghost->getY() == mario.getY()) {
            b->deathreason(GHOST_HIT);
            return true;
        }
    }

    return false;
}

bool Ghostim::removeGhost(int x, int y) {
    for (size_t i = 0; i < GhostimArray.size(); i++) {
        if (GhostimArray[i]->getX() == x && GhostimArray[i]->getY() == y) {
            GhostimArray.erase(GhostimArray.begin() + i);
            return true;
        }
    }
    return false;
}

