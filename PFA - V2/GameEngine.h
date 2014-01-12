#pragma once

#include <stack>
#include <vector>
#include "IEntity.h"
#include "IEngine.h"
#include "KeyboardControler.h"

class GameEngine : public IEngine
{
public:
	GameEngine(std::stack<IScreen *>&);
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
	std::stack<IScreen *>	&_states;

};

