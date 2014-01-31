#pragma once
#include <vector>
#include <SFGUI/SFGUI.hpp>

#include "IEntity.h"
#include "Compartment.h"
#include "Water.h"
#include "Camera.h"

class Player : public IEntity
{
public:
	Player(sf::Vector2f &pos, Camera *cam);
	void doAction(IEntity* other);
	void getAction(IEntity* other);
	void drink(Water *);
	std::string const &getName() const;
	void setName(std::string const &);
	void Animate(std::string const & string_anim);
	void draw();
	void setCamPos(sf::Vector2f &); // TMP LE TEMPS QUON AI LA BONNE CLASS
	void setPosition(sf::Vector2f &pos);
	
	sf::Vector2f  getPosition() const;
	void setPath(std::list<std::pair<float, float> >& );
	
	void move(sf::Vector2f & pos);
	int getDamage(void) const;
	Type getType() const;
	sfg::Box::Ptr getBox();
	sfg::Notebook::Ptr _book;
	bool addEntityInInventory(IEntity *entity);
	bool delEntityInInventory(Type);
	bool delEntityInInventory(IEntity *);
	void moveToNextWP();
	//sf::Rect & getCollisionBox(void);

	//TODO : Changer en compartments pour l'inventaire

	sf::Image					_img; //TMP
	std::vector<Compartment *>	_inventoryPlayer;
	// std::vector<IEntity *> _inventary;
protected:
private:
	void					createBox();


	Camera						*_camera;
	std::list<std::pair<float, float> >	_path;
	
	sf::RectangleShape			_rect;
	sf::Vector2f				_pos;
	sf::Vector2f _posDisp;
	unsigned int _sizeInventory;
	std::string _name;
	int _life;
	int _damages;
	int _water;
	int _food;
	bool _isSick;
	sfg::Box::Ptr _inventory;
};