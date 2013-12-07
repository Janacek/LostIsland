#pragma once

#include "Singleton.h"
#include "GameEngine.h"
#include "GraphicEngine.h"
#include "PhysicEngine.h"

class Game
{
public:
	Game(void);
	~Game(void);
   void launch(void);

protected:
private:
   GraphicEngine *_graphicEngine;
   GameEngine	 *_gameEngine;
   PhysicEngine *_physicEngine;

   sf::Clock			_cl;
};

