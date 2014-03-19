#pragma once

#include <map>
#include <functional>

#include <SFML/Audio/Music.hpp>

#include "IScreen.h"

#include "Player.h"
#include "Velociraptor.h"

#include "InventoryWindow.h"
#include "Crafting.h"
#include "Stuff.h"
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
	stateName getStateName() const;

	virtual std::string &serialize() const;
	virtual void deserialize(std::ifstream &) throw (MyException);

	void drawEntities();
	void drawEntitiesInfos();
	void redrawEntities();

 
protected:
private:
	InventoryWindow			*_inventory;
	bool				_gameOver;

	Crafting			*_crafting;
	Stuff				*_stuff;
	Camera				_camera;

	void				checkDrawInventory();
	void				checkEntitySelection();
	void				drawSelectionZone();
	void				updateSelectionZone();


	PhysicEngine			*_physicEngine;
	bool					_activeInventary;
	Map						*_map;
	sf::Time				_t;
	sf::Clock				_clickClock;
	std::vector<Player *>	_players;
	std::vector<AEntity *>	_entities;

	bool					_isRunning;
	IScreen					* _next;

	sf::RectangleShape		_mousePicture;
	sf::Vector2i			_posSelectedArea;
	void					drawPlayerInformations(Player *, sf::Vector2f const &) const;

	/*
	** Loading screen;
	*/
	sf::Image				*_loadingScreen;
	bool					_loaded;
	std::string				_loadingText;
	sf::Text				_loadingSfText;



	/* ENDING */
	sf::Vector2f			_truckPosition;
	sf::Vector2f			_credit0;
	sf::Music				*_music;
	bool					_playMusic;
	void					drawText(std::string text, int x, int y, int size);

	sf::Music				*_Amusic;

};