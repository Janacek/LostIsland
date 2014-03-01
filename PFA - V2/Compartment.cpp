#include "Compartment.h"
#include "ImageManager.h"
#include "Singleton.h"
#include <sstream>
#include <algorithm>
#include <iostream>

Compartment::Compartment(AEntity *entity)
{
	if (entity != NULL)
	{
		this->addElement(entity);
	}
}

Compartment::~Compartment()
{
	//del les ressources
}
void Compartment::addElement(AEntity *entity)
{
	this->_elements.push_back(entity);
	if (this->_elements.size() == 1)
		this->_img = (*ImageManager::getInstance().get(entity->getType())).copyToImage();
}

void Compartment::delAllElement()
{
	this->_elements.clear();
}

bool Compartment::delElement(AEntity *entity)
{
	return true;
}

int Compartment::getSize() const
{
	return this->_elements.size();
}

Type Compartment::getType() const
{
	if (this->_elements.size() > 0)
		return this->_elements.front()->getType();
	return BADTYPE;
}

bool Compartment::delElement()
{
	if (this->_elements.size() != 0)
	{
		this->_elements.pop_back();
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
std::list<AEntity *> Compartment::getElements(int nbr)
{	
	std::cout << "ELELEMEM : " << this->_elements.size() << std::endl;
	int i = 0;
	std::list<AEntity *> list;
	if (nbr == 0)
		return this->_elements;
	for (AEntity *u : this->_elements)
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