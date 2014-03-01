#include "EntityFactory.h"
/*TODO include toutes les entities nécessaire*/

EntityFactory::EntityFactory()
{
	this->_entityMap["WOODEN_PLANK"] = &EntityFactory::createWoodenPlank;
	this->_entityMap["BUCKET"] = &EntityFactory::createBucket;
	this->_entityMap["BOWL"] = &EntityFactory::createBowl;
	this->_entityMap["CAMPFIRE"] = &EntityFactory::createCampfire;
	this->_entityMap["SWORD"] = &EntityFactory::createSword;
	this->_entityMap["JACKET"] = &EntityFactory::createJacket;
	this->_entityMap["FABRIC"] = &EntityFactory::createFabric;
	this->_entityMap["PANTS"] = &EntityFactory::createPants;
	this->_entityMap["ROPE"] = &EntityFactory::createRope;
	this->_entityMap["STEW"] = &EntityFactory::createStew;
	this->_entityMap["INFUSION"] = &EntityFactory::createInfusion;
	this->_entityMap[""] = &EntityFactory::badType;
}

AEntity *EntityFactory::makeEntity(std::string const &type)
{
	return (this->*_entityMap[type])();
}

AEntity *EntityFactory::badType()
{
	return NULL;
}

AEntity *EntityFactory::createWoodenPlank() 
{
	return NULL;
}

AEntity *EntityFactory::createBucket() 
{
	return NULL;
}

AEntity *EntityFactory::createBowl() 
{
	return NULL;
}

AEntity *EntityFactory::createCampfire() 
{
	return NULL;
}

AEntity *EntityFactory::createSword() 
{
	return NULL;
}

AEntity *EntityFactory::createJacket() 
{
	return NULL;
}

AEntity *EntityFactory::createFabric() 
{
	return NULL;
}

AEntity *EntityFactory::createPants() 
{
	return NULL;
}

AEntity *EntityFactory::createRope() 
{
	return NULL;
}

AEntity *EntityFactory::createStew() 
{
	return NULL;
}

AEntity *EntityFactory::createInfusion() 
{
	return NULL;
}

EntityFactory::~EntityFactory()
{
	this->_entityMap.clear();
}
