#pragma once

#include "IEntity.h"

class MapEnvironment
{
public:
	MapEnvironment();
	~MapEnvironment();
	IEntity			*_component;
};