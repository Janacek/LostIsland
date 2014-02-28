#pragma once

#include "AEntity.h"
#include <list>

class Compartment
{
public:
	Compartment(AEntity *);
	~Compartment();
	int							getSize() const;
	Type						getType() const;
	void						addElement(AEntity *);
	std::list<AEntity *>		getElements(int nbr = 0);
	bool						delElement(AEntity *);
	void						delAllElement();
	sf::Image const				&getImage() const;
	bool						delElement();

private:
	std::list<AEntity *>		_elements;

	sf::Image					_img;
	
};

bool operator==(Compartment *, Type);
bool operator!=(Compartment *, Type);