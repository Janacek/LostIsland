#pragma once

#include <list>
#include "IEngine.h"
#include "IEntity.h"

enum stateName
{
	GAME,
	MENU,
	OPTIONS,
};

class IScreen
{
public:
	virtual void draw() = 0;
	virtual void initialize(void) = 0;
	virtual IScreen * getNextState(void) = 0;
	virtual void release(void) = 0;
	virtual  bool isRunning(void) const = 0;
	virtual void update(void) = 0;
	virtual stateName getStateName() const = 0;

protected:
private:

};