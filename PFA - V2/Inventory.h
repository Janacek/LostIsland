#pragma once

#include	<vector>
#include	 <deque>
#include	<list>
#include	<SFML/Graphics.hpp>
#include	"InventaryWindow.h"
#include	"Player.h"
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
	InventaryWindow				 *_mainInventory;
private:
	void printInventory() const;
	bool isInCompartment(Compartment &) const;
	void printInventory(Onglet *o) const;
	void checkInputOnglet();
	void selectOnglet(Onglet *);

	Onglet						*_selectOnglet;
	//pointeur pour pas avoir a cr�er un constructeur vide
	
	std::vector<Player *>			_players;
//	std::deque<Compartment *> _compartment;
	unsigned int				_sizeInventory;
	
};

