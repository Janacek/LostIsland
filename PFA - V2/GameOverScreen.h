#pragma once

#include "IScreen.h"
#include "StartScreen.h"

class GameOverScreen : public IScreen
{
public:
	GameOverScreen();
	virtual ~GameOverScreen();

	void draw();
	void initialize();
	IScreen *getNextState();
	void release(void);
	bool isRunning(void) const;
	void update(void);
	stateName getStateName() const;
	void events(sf::Event &);

private:
	bool				_isRunning;
	IScreen				*_next;

	sf::Image			*_gameOverScreen;
	int					_currentPosition;
};