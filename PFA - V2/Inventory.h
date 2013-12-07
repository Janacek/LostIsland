#pragma once

#include	<vector>
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
	void deleteEntityInInventory(IEntity *);
private:
	
	sf::RectangleShape _mainInventory;
	std::vector<IEntity *> _ressources;
	std::vector<Compartment> _compartment;

};

