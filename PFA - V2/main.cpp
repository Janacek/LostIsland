#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "Game.h"
#include "sqlite3.h"

using namespace std;

int main()
{
	Game	new_game;
	new_game.launch();
	return 0;
}	