#pragma once
#include "IScreen.h"
#include "OptionScreen.h"
#include "FontManager.h"

#include <SFML/Audio/Music.hpp>

class StartScreen : public IScreen
{
public:
	StartScreen(); //ALORS, on met un boolean dans chaque state des qu'on veut un new slide on set un ptr IScreen dans se state au next state , dans le gamemanager si il est false on get le state suivant dans le state
	virtual ~StartScreen();

	void draw();
	void initialize(void);
	IScreen * getNextState(void);
	void release(void);
	bool isRunning(void) const;
	void update(void);
	stateName getStateName() const;
	void events(sf::Event &);

protected:
private:
	bool					_isRunning;
	std::vector<sf::Text *> _entries;
	IScreen					* _next;
	int						_curPos;
	sf::RectangleShape		*_selector;
	sf::Time				_timeElapsed;
	sf::Clock				*_choiceClock;


	sf::Image				*_menuScreen;

	/*
	** LOL I'M SO DRUNK !§
	*/
	sf::Music				*_music;
};