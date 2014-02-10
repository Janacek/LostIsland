#pragma once

#include <list>
#include <vector>
#include "IEntity.h"
#include "IEngine.h"
#include "KeyboardControler.h"

class GameEngine : public IEngine
{
public:
	GameEngine(std::list<IScreen *>&);
	~GameEngine();
	bool getIsRunning() const;
	void init();
	void update();

	void PushState(IScreen *state);
	void SetState(IScreen *state);
	void PopState(void);

protected:
private:
	bool _isRunning;
	KeyboardControler		_controler;
	sf::Clock				*_cl;
	std::list<IScreen *>	&_states;

	sf::Clock				_stateClock;
	float					_timeToLive;
};

