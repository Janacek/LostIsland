#include "Compartment.h"
#include "ImageSingleton.h"
#include "Singleton.h"
#include <sstream>
#include <algorithm>
#include <iostream>

Compartment::Compartment(IEntity *entity)
{
	this->_numberElements = 0;
	if (entity != NULL)
	{
		this->addElement(entity);
	}
}

Compartment::~Compartment()
{
	//del les ressources
}
void Compartment::addElement(IEntity *entity)
{
	this->_elements.push_back(entity);
	if (this->_numberElements == 0)
		this->_img = (*ImageSingleton::getInstance().get(entity->getType())).copyToImage();
	++this->_numberElements;
}

void Compartment::delAllElement()
{
	this->_elements.clear();
	this->_numberElements = 0;
}

bool Compartment::delElement(IEntity *entity)
{
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

sf::Image const&Compartment::getImage() const
{
	return this->_img;
}

//retourne une liste de pointeurs contenus dans le compartiment .. Peut etre utile, evite de faire des new
//si pas de param (cas nbr = 0) retourne toute la list
std::list<IEntity *> Compartment::getElements(int nbr)
{	
	std::cout << "ELELEMEM : " << this->_elements.size() << std::endl;
	int i = 0;
	std::list<IEntity *> list;
	if (nbr == 0)
		return this->_elements;
	for (IEntity *u : this->_elements)
	{
		list.push_back(u);
		++i;
		if (i == nbr)
			return list;		
	}
	return list;
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