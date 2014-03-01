#pragma once

#include "AEntity.h"
#include <map>
class EntityFactory
{
public:
	EntityFactory();
	AEntity *makeEntity(std::string const &);
	~EntityFactory();
private:
	
	AEntity *createWoodenPlank();
	AEntity *createBucket();
	AEntity *createBowl();
	AEntity *createCampfire();
	AEntity *createSword();
	AEntity *createJacket();
	AEntity *createFabric();
	AEntity *createPants();
	AEntity *createRope();
	AEntity *createStew();
	AEntity *createInfusion();
	AEntity *badType();
	std::map<std::string, AEntity *(EntityFactory::*)()> _entityMap;
};

