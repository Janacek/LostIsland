#include "Singleton.h"

Singleton Singleton::m_instance=Singleton();

Singleton::Singleton()
{
	_animClock = new sf::Clock();
}

Singleton::~Singleton()
{

}

Singleton& Singleton::getInstance()
{
	return m_instance;
}