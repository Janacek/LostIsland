#pragma once

#include <map>
#include <functional>
#include "IScreen.h"
#include "Player.h"
#include "Inventory.h"
#include "Crafting.h"
#include "Stuff.h"
#include "Map.h"
#include "GestionClick.h"

class GameScreen : public IScreen
{
public:
	GameScreen();

	void draw(std::vector<IEntity *> &players,std::list<IEntity *> &entities);
	void initialize(void);
	IScreen * getNextState(void);
	void release(void);
	bool isRunning(void) const;
	void update(void);

protected:
private:
	void				updateStatistics(sf::Time &elapsedTime);
	void				checkInput();
	void				checkClicks();
	void				saveClick(bool click);
	void				updateObjectsPos();

	GestionClick		_gestionClick;
	bool				_activeInventary;
	Map					*_map;
	sf::Time			_t;
	sf::Clock			_clickClock;
	std::vector<Player *>	_players;
	Inventory			*_inventory;
	Crafting			*_crafting;
	Stuff				*_stuff;
	sf::Text			_statisticsText;
	std::size_t			_statisticsNumFrames;
	sf::Time			_statisticsUpdateTime;
	sf::Font			_font;
	bool				_isRunning;
	IScreen				* _next;
	sf::Text			* _statisticText;
	struct s_action			_leftClickPressed;
	struct s_action			_leftClickReleased;
	struct s_action			_rightClickPressed;
	struct s_action			_rightClickReleased;

	GestionClick			_gc;
};