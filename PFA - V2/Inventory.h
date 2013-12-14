#pragma once

#include	<vector>
#include	 <deque>
#include	<list>
#include	<SFML/Graphics.hpp>
#include	"InventaryWindow.h"
#include	"Player.h"
#include	"AWindow.h"
#include	"IEntity.h"
#include	"Compartment.h"
#include	"Singleton.h"


class Inventory
{
public:
	Inventory(std::vector<Player *> &);
	~Inventory(void);
	void update(void);
	void draw(void);
	void addEntityInInventory(IEntity *);
	void deleteEntityInInventory(Compartment *);
	bool close() const;
	
	//tmp

private:
	void checkInputs();
	void updateViewCompartments();
	void printInventory() const;
	bool isInCompartment(Compartment &) const;
	void organizeCompartment(Compartment *);
	void checkInputOnglet();
	void selectOnglet(Onglet *);

	Onglet						*_selectOnglet;
	//pointeur pour pas avoir a créer un constructeur vide
	InventaryWindow				 *_mainInventory;
	std::vector<Player *>			_players;
//	std::deque<Compartment *> _compartment;
	unsigned int				_sizeInventory;
	std::map<Type, std::string> _enumStrings;
};

