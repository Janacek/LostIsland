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
	bool delElement(IEntity *);
	bool delElement();

private:
	std::list<IEntity *> _elements;
	unsigned int _numberElements;
	
};

bool operator==(Compartment *, Type);
bool operator!=(Compartment *, Type);