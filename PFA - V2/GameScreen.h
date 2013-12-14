#pragma once

#include <map>
#include "IScreen.h"
#include "Player.h"
#include "Inventory.h"
#include "Crafting.h"
#include "Stuff.h"
#include "Map.h"

enum Screens
{
	INVENTORY,
	STUFF,
	CRAFTING,
	GAMESCREEN
};

struct			s_action
{
	Screens		_screen;
	Compartment *_compartment;
};

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
	bool				_activeInventary;
	Map					*_map;
	sf::Clock			_clickClock;
	std::vector<Player *>	_players;
	Inventory			*_inventory;
	Crafting			*_crafting;
	Stuff				*_stuff;
	void				updateStatistics(sf::Time &elapsedTime);
	void				checkInput();
	sf::Text			_statisticsText;
	std::size_t			_statisticsNumFrames;
	sf::Time			_statisticsUpdateTime;
	sf::Time			_t;
	sf::Time			_timeKey;
	sf::Font			_font;
	bool				_isRunning;
   IScreen				* _next;
   sf::Text				* _statisticText;
  // std::map<Screens, std::map<Screens, void (AWindow::*)(s_action&, s_action&)> > _map;
};