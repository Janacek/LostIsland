#pragma once

#include    "AWindow.h"

class		GestionClick
{
public:
	GestionClick(void);
	
	void	swap(s_action&, s_action&);
	void	add(s_action&, s_action&);
	void	drop(s_action&, s_action&);
	std::map<Screens, std::string> _enumToString;
	~GestionClick(void);

	void	createCorrelationTable();
	void	createInventoryTable();
	void	createStuffTable();
	void	createCraftingTable();


	typedef void (GestionClick::*gestionClick)(s_action&, s_action&);

	void												callFunction(s_action&, s_action&);
	std::map<Screens, std::map<Screens, gestionClick> > _correlationTable;
	gestionClick										_caller;
};

