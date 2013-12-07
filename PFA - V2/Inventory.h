#pragma once

#include	<vector>
#include <deque>
#include	<list>
#include	<SFML/Graphics.hpp>
#include	"IEntity.h"
#include	"Compartment.h"
#include	"Singleton.h"


class Inventory
{
public:
	Inventory(void);
	~Inventory(void);
	void update(void);
	void draw(void);
	void addEntityInInventory(IEntity *);
	void deleteEntityInInventory(Compartment *);
	
private:
	
	void checkInputs();
	void printInventory() const;
	bool isInCompartment(Compartment &) const;
	void organizeCompartment(Compartment *);

	sf::RectangleShape _mainInventory;
	std::deque<Compartment *> _compartment;
	unsigned int			_sizeInventory;
	std::map<Type, sf::Sprite *> _mapSprites;
	std::map<Type, std::string> _enumStrings;
};

