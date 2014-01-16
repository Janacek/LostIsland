#pragma once
#include "IScreen.h"
#include "OptionScreen.h"
#include "FontManager.h"

class StartScreen : public IScreen
{
public:
	StartScreen(); //ALORS, on met un boolean dans chaque state des qu'on veut un new slide on set un ptr IScreen dans se state au next state , dans le gamemanager si il est false on get le state suivant dans le state

	void draw();
	void initialize(void);
	IScreen * getNextState(void);
	void release(void);
	bool isRunning(void) const;
	void update(void);
	stateName getStateName() const;

protected:
private:
	bool					_isRunning;
	std::vector<sf::Text *> _entries;
	IScreen					* _next;
	int						_curPos;
	sf::RectangleShape		*_selector;
	sf::Time				_timeElapsed;
	sf::Clock				*_choiceClock;
};