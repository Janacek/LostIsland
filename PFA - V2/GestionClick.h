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
};

