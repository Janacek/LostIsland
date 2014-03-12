#include "EntityFactory.h"
#include "WoodenPlank.h"
#include "Bucket.h"
#include "Bowl.h"
#include "Campfire.h"
#include "Sword.h"
#include "Jacket.h"
#include "Fabric.h"
#include "Pants.h"
#include "Rope.h"
#include "Stew.h"
#include "Infusion.h"
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
	return new WoodenPlank;
}

AEntity *EntityFactory::createBucket() 
{
	return new Bucket;
}

AEntity *EntityFactory::createBowl() 
{
	return new Bowl;
}

AEntity *EntityFactory::createCampfire() 
{
	return new Campfire; //Pas de contructeur pas defaut pour le moment
}

AEntity *EntityFactory::createSword() 
{
	return new Sword;
}

AEntity *EntityFactory::createJacket() 
{
	return new Jacket;
}

AEntity *EntityFactory::createFabric() 
{
	return new Fabric;
}

AEntity *EntityFactory::createPants() 
{
	return new Pants;
}

AEntity *EntityFactory::createRope() 
{
	return new Rope;
}

AEntity *EntityFactory::createStew() 
{
	return new Stew;
}

AEntity *EntityFactory::createInfusion() 
{
	return new Infusion;
}

EntityFactory::~EntityFactory()
{
	this->_entityMap.clear();
}
