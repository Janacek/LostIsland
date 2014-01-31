#include "Compartment.h"
#include <sstream>
#include <algorithm>
#include <iostream>

Compartment::Compartment(IEntity *entity)
{
	if (entity != NULL)
	{
		this->_numberElements = 1;
		this->_elements.push_back(entity);
	}
	else
	{
		this->_numberElements = 0;
	}	
}

Compartment::~Compartment()
{
	//del les ressources
}
void Compartment::addElement(IEntity *entity)
{
	this->_elements.push_back(entity);
	++this->_numberElements;
}

bool Compartment::delElement(IEntity *entity)
{
	/*if (this->_elements.end == std::remove(this->_elements.begin(), this->_elements.end(), entity))
		return false;
	this->_numberElements--;*/
	return true;
}

int Compartment::getSize() const
{
	return this->_numberElements;
}

Type Compartment::getType() const
{
	if (this->_elements.size() > 0)
		return this->_elements.front()->getType();
	return BADTYPE;
}

bool Compartment::delElement()
{
	if (this->_numberElements != 0)
	{
		this->_elements.pop_back();
		--this->_numberElements;
		return true;
	}
	return false;
}

bool operator==(Compartment *c, Type type)
{
	if (c->getSize() > 0)
		return c->getType() == type;
	return false;
}

bool operator!=(Compartment *c, Type type)
{
	if (c->getSize() > 0)
		return c->getType() != type;
	return true;
}