#pragma once

#include "IScreen.h"
#include "Inventory.h"
#include "Map.h"

class GameScreen : public IScreen
{
public:
	GameScreen();
   
   void draw(std::list<IEntity *> players,std::list<IEntity *> entities);
   void initialize(void);
   IScreen * getNextState(void);
   void release(void);
   bool isRunning(void) const;
   void update(void);

protected:
private:
	Map					*_map;
	Inventory			*_inventory;
	void				updateStatistics(sf::Time &elapsedTime);
	sf::Text			_statisticsText;
	std::size_t			_statisticsNumFrames;
	sf::Time			_statisticsUpdateTime;
	sf::Time			_t;
	sf::Font			_font;
	bool				_isRunning;
   IScreen				* _next;
   sf::Text				* _statisticText;
};