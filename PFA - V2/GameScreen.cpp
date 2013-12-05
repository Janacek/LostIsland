#include "GameScreen.h"
#include "Inventory.h"

GameScreen::GameScreen()
{
	_isRunning = true;
}

void GameScreen::draw(std::list<IEntity *> entities)
{
	this->_inventory->draw();
}

void GameScreen::initialize(void)
{
	this->_inventory = new Inventory;
}

IScreen * GameScreen::getNextState(void)
{
	return this->_next;
}

void GameScreen::release(void)
{
}

bool GameScreen::isRunning(void) const
{
	return this->_isRunning;
}

void GameScreen::update(void)
{
}