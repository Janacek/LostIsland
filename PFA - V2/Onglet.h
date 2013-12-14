#pragma once

#include "AWindow.h"
#include "Player.h"

class Onglet : public sf::RectangleShape
{
public:
	Onglet(Player *, std::string const &title, float sizeX, float sizeY, float posX, float posY);
	void draw();
	void update();
	std::string getName() const;
	void setisSelected(bool );
	bool isSelected() const;
	~Onglet(void);

	Player *_player;
private:
	
	sf::Text _name;
	sf::Font *_font;
	bool _isSelected;
};

