#pragma once

#include <map>
#include <functional>
#include "IScreen.h"

#include "Player.h"


#include "InventoryWindow.h"
#include "Crafting.h"
#include "RessourcesWindow.h"
#include "PhysicEngine.h"
#include "StartScreen.h"
#include "FontManager.h"
#include "OnScreenLogs.h"
#include "StartScreen.h"

class GameScreen : public IScreen
{
public:
	GameScreen();
	virtual ~GameScreen();

	void draw();
	void initialize(void);
	IScreen					*getNextState(void);
	void release(void);
	bool isRunning(void) const;
	void update(void);
	void events(sf::Event &);
	std::vector<Player *> &getPlayers();
	void switchTabs();
	stateName getStateName() const;
	sf::Vector2f pos;
	void mouseLeftPress(int index);
	void validDrop(int);
	void dropRessource();

	InventoryWindow			*_inventory; //Oups
protected:
private:
	Crafting			*_crafting;
	Camera				_camera;
	void				updateStatistics(sf::Time &elapsedTime);
	void				checkDrop(sf::Event &e);
	void				checkInput();
	void				drawMouse();
	void				checkClose();
	void				checkQuit(sf::Event &e);
	void				checkDrawInventory();
	void				checkClicks();
	void				saveClick(bool click);
	void				updateObjectsPos();
	bool				checkImpossibleCase() const;
	void				checkEntitySelection();
	void				drawSelectionZone();
	void				updateSelectionZone();
	PhysicEngine			*_physicEngine;
	GestionClick			_gestionClick;
	bool					_activeInventary;
	bool					_activeWinRessources;
	Map						*_map;
	sf::Time				_t;
	sf::Clock				_clickClock;
	std::vector<Player *>	_players;
	std::vector<IEntity *>	_entities;
	
	RessourcesWindow		*_winRessource;
	sf::Text				_statisticsText;
	std::size_t				_statisticsNumFrames;
	sf::Time				_statisticsUpdateTime;
	bool					_isRunning;
	IScreen					* _next;
	sf::Text				* _statisticText;
	sf::RectangleShape		_mousePicture;
	s_action				_leftClickPressed;
	s_action				_leftClickReleased;
	s_action				_rightClickPressed;
	s_action				_rightClickReleased;
	
	Compartment				*_dropCompartment;

	sf::Vector2i			_posSelectedArea;

	void					drawPlayerInformations(Player *, sf::Vector2f const &) const;

	std::list<IEntity *>	_sortList;

	/*
	** Loading screen;
	*/
	sf::Image				*_loadingScreen;
	bool					_loaded;
	std::string				_loadingText;
	sf::Text				_loadingSfText;

	/*--------TEST---------*/
	std::vector<IEntity *> _one;
	std::vector<IEntity *> _two;
	std::vector<IEntity *> _tree;
};