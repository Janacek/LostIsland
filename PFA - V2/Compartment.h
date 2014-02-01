#pragma once

#include "Singleton.h"
#include "IEntity.h"
#include <list>

class Compartment
{
public:
	Compartment(IEntity *);
	~Compartment();
	int getSize() const;
	Type getType() const;
	void addElement(IEntity *);
	std::list<IEntity *> getElements(int nbr = 0);
	bool delElement(IEntity *);
	void delAllElement();
	sf::Image const&getImage() const;
	bool delElement();

private:
	std::list<IEntity *>	 _elements;

	sf::Image				_img;
	unsigned int			 _numberElements;
	
};

bool operator==(Compartment *, Type);
bool operator!=(Compartment *, Type);