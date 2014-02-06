#pragma once
#include <vector>
#include <SFGUI/SFGUI.hpp>

#include "IEntity.h"
#include "Compartment.h"
#include "Water.h"
#include "Camera.h"
#include "Animation.h"

class Player : public IEntity
{
public:
	Player(sf::Vector2f &pos, Camera *cam);
	void doAction(IEntity* other);
	void getAction(IEntity* other);
	void drink(Water *);
	std::string const &getName() const;
	void setName(std::string const &);
	void loadAnimation(std::string const & string_anim, float speed);
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
	Compartment	*getCompartment(int index);
	int			posInventory(IEntity *);
	void moveToNextWP();
	void update();
	//sf::Rect & getCollisionBox(void);

	//TODO : Changer en compartments pour l'inventaire

	sf::Image					_img; //TMP
	// std::vector<IEntity *> _inventary;


protected:

	/*
	** Player's camera and misc
	*/
	void					createBox();
	
	Animation					*_anim;
	Camera						*_camera;


	/*
	** Player pathfinding
	*/
	std::list<std::pair<float, float> >	_path;
	
	/*
	** Player's name (could be with miscs)
	*/
	std::string					_name;

	/*
	** Player position
	*/
	sf::RectangleShape			_rect;
	sf::Vector2f				_pos;

	sf::Vector2f _posDisp;
	unsigned int _sizeInventory;
	

	/*
	** Player inventory
	*/

	std::vector<Compartment *>	_inventoryPlayer;
	


	/*
	** Player state
	*/
	float						_life;
	float						_damages;
	float						_water;
	float						_food;
	bool						_isSick;

	sfg::Box::Ptr				_inventory;
	sf::Clock					_referenceClock;

	double						_hungerClock;
	double						_thirstClock;
	double						_lifeClock;
	double						_oldDt;

	/*
	** Selection of the player.
	*/
	bool						_isSelected;
public:
	void						setSelected(bool const);
	bool						const getSelected() const;
};