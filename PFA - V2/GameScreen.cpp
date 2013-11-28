#include "GameScreen.h"

GameScreen::GameScreen()
{
	_isRunning = true;
}

void GameScreen::draw(std::list<IEntity *> entities)
{
}

void GameScreen::initialize(void)
{

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