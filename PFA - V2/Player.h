#pragma once
#include <vector>
#include "IEntity.h"
#include "Compartment.h"

class Player : public IEntity
{
public:
	Player(sf::Vector2f &pos);
	void doAction(IEntity* other);
	void getAction(IEntity* other);
	std::string const &getName() const;
	void setName(std::string const &);
	void Animate(std::string const & string_anim);
	void draw();
	void setCamPos(sf::Vector2f &); // TMP LE TEMPS QUON AI LA BONNE CLASS
	void setPosition(sf::Vector2f &pos);
	void move(sf::Vector2f & pos);
	int getDamage(void) const;
	Type getType() const;
	void addCompartment(sf::RectangleShape &);
	void addEntityInInventory(IEntity *entity);
	//sf::Rect & getCollisionBox(void);

	//TODO : Changer en compartments pour l'inventaire
	std::vector<Compartment *> _compartments;
	// std::vector<IEntity *> _inventary;
protected:
private:

	sf::RectangleShape _rect;
	sf::Vector2f _cam;
	sf::Vector2f _pos;
	sf::Vector2f _posDisp;
	unsigned int _sizeInventory;
	std::string _name;
	int _life;
	int _damages;
	int _water;
	int _food;
	bool _isSick;

};