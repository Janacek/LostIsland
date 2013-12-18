#pragma once

#include <list>
#include "IEngine.h"
#include "IEntity.h"

class IScreen
{
public:
	virtual void draw(std::vector<IEntity *> &players, std::list<IEntity *> &entities) = 0;
	virtual void initialize(void) = 0;
	virtual IScreen * getNextState(void) = 0;
	virtual void release(void) = 0;
	virtual  bool isRunning(void) const = 0;
	virtual void update(void) = 0;

protected:
private:

};