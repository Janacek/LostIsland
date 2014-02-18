#pragma once

#include <list>
#include "IScreen.h"
#include "Map.h"

class IEngine
{
	public:
   virtual void init() = 0;
   virtual void update() = 0;
};
