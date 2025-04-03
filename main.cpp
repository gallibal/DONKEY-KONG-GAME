#include "Game.h"
#include "AutoGame.h"
int main(int argc,char** argv)
{
    GenralMarioGame* g;
    bool isSave = argc > 1 && std::string(argv[1]) == "-save";

    bool isLoad = argc > 1 && std::string(argv[1]) == "-load";
    bool isSilent = isLoad && argc > 2 && std::string(argv[2]) == "-silent";
  
    if (isLoad)
    {
        g = new AutoGame(isSilent);
    }
    else
        g = new Game(isSave);
    g->Run();
    delete g;

}