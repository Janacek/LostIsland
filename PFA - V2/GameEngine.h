#pragma once

#include <stack>
#include <vector>
#include "IEntity.h"
#include "IEngine.h"
#include "GameEvents.h"
#include "KeyboardControler.h"

class GameEngine : public IEngine
{
public:
	GameEngine(Map *&, std::stack<IScreen *>&);
	~GameEngine();
	bool getIsRunning() const;
	void init();
	void update(std::vector<IEntity *> &players, std::list<IEntity *> &entities);

	void PushState(IScreen *state);
	void SetState(IScreen *state);
	void PopState(void);

protected:
private:
	bool _isRunning;
	GameEvents				*_gameEvents;
	KeyboardControler		_controler;
	sf::Clock				*_cl;
	Map						*&_map;
	std::stack<IScreen *>	&_states;

};

