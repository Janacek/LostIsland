#pragma once

#include <map>
#include <functional>
#include "IScreen.h"

#include "Player.h"
#include "Bunny.h"

#include "InventoryWindow.h"
#include "Map.h"
#include "GestionClick.h"
#include "PhysicEngine.h"
#include "StartScreen.h"
#include "FontManager.h"

class GameScreen : public IScreen
{
public:
	GameScreen();

	void draw();
	void initialize(void);
	IScreen					*getNextState(void);
	void release(void);
	bool isRunning(void) const;
	void update(void);
	void events(sf::Event &);
	void switchTabs();
	stateName getStateName() const;
	sf::Vector2f pos;
	void mouseLeftPress(int index);
	void validDrop(int);
	void dropRessource();
protected:
private:
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
	PhysicEngine			*_physicEngine;
	GestionClick			_gestionClick;
	bool					_activeInventary;
	Map						*_map;
	sf::Time				_t;
	sf::Clock				_clickClock;
	std::vector<Player *>	_players;
	std::vector<IEntity *>	_entities;
	InventoryWindow			*_inventory;
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
	GestionClick			_gc;

	sf::Vector2i			_posSelectedArea;
};