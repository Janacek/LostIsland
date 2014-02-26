#pragma once
#include <vector>
#include <SFGUI/SFGUI.hpp>
#include "Compartment.h"
#include "Camera.h"
#include "AnimatedSprite.h"

class Water;
class InventoryWindow;

enum Direction
{
	UP,
	DOWN,
	RIGHT,
	LEFT
};

class Player : public IEntity
{
public:
	Player(sf::Vector2f &pos, Camera *cam);
	void doAction(IEntity* other);
	void getAction(IEntity* other);
	void drink(Water *);
	void eat(int);
	std::string const &getName() const;
	void setName(std::string const &);
	void loadAnimation(std::string const & string_anim, float speed);
	void draw(sf::RenderTexture *, sf::Shader &);
	void draw(sf::RenderTexture *);
	void setCamPos(sf::Vector2f &); // TMP LE TEMPS QUON AI LA BONNE CLASS
	void setPosition(sf::Vector2f &pos);

	sf::Vector2f  getPosition() const;
	void setPath(std::list<std::pair<float, float> >&);

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
	void update(Map &);
	float getPathToGo() const;
	void setPathToGo(float f);
	void addToPathToGo(float f);
	bool getIsMoving() const;
	bool getIsStopped() const{ return false; }
	bool getIsAMovingEntity() const{ return true; }
	void setMap(Map *map) { _map = map; };
	void setInventory(InventoryWindow *inventory) { _inventoryWindow = inventory; };
	Map *getMap() { return _map; };


	sf::IntRect & getCollisionBox(void);

	//TODO : Changer en compartments pour l'inventaire

	sf::Image					_img; //TMP
	// std::vector<IEntity *> _inventary;

protected:

	/*
	** Player's camera and misc
	*/
	void					createBox();

	Animation					*_curAnim;
	Animation					*_walkDownAnim;
	Animation					*_walkRightAnim;
	Animation					*_walkLeftAnim;
	Animation					*_walkUpAnim;
	Animation					*_idleDownAnim;
	Animation					*_idleRightAnim;
	Animation					*_idleLeftAnim;
	Animation					*_idleUpAnim;
	Animation					*_hitUpAnim;
	Animation					*_hitRightAnim;
	Animation					*_hitLeftAnim;
	Animation					*_hitDownAnim;
	Animation					*_attackUpAnim;
	Animation					*_attackDownAnim;
	Animation					*_attackRightAnim;
	Animation					*_attackLeftAnim;
	Animation					*_deathAnim;
	Animation					*_victoryAnim;
	AnimatedSprite				*_animatedSprite;

	void					addInInventoryWindow(IEntity *, int pos);


	Camera						*_camera;
	sf::IntRect				_boxCollider;


	/*
	** Player pathfinding
	*/
	sf::Clock					_mvtClock;
	float						_oldDtMvt;

	float								_speed;
	std::list<std::pair<float, float> >	_path;
	float								_pathToGo;
	bool								_isMoving;
	bool								_hasAPath;
	bool								_isPathNotFound;
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
public:
	float						_life;
	int							_damages;
	float						_water;
	float						_food;
	bool						_isSick;
	bool						_isPathFound;
	sfg::Box::Ptr				_inventory;
	sf::Clock					_referenceClock;

	double						_hungerClock;
	double						_thirstClock;
	double						_lifeClock;
	double						_actionClock;
	double						_oldDt;

	//////////////////////////
	//  PLAYER'S OBJECTIVE
	//////////////////////////
	IEntity						*_objective;
	Type						_target;
	/*
	** Selection of the player.
	*/
	bool						_isSelected;
public:
	void						doActionOnEntity();
	void						changeMapEntity(Map&);
	void						setSelected(bool const);
	bool						const getSelected() const;
	bool const getIsPathFound() const { return _isPathFound; }
	void setIsPathFound(bool n) { _isPathFound = n; }
	void setTarget(Type);
	std::list<std::pair<float, float>> getPath() const { return this->_path; };
	sf::FloatRect getBoxCollider() const;
private:
	float						_cursorTime;
	void						changeAnimation(sf::Vector2f&, std::pair<float, float>);
	void						changeToIdleAnim();
	Map							*_map;
	InventoryWindow				*_inventoryWindow;
	float						_timeAttack;
	
public:
	const float					HUNGER_CLOCK = 6.f;
	const float					THIRST_CLOCK = 3.f;
	const float					HEALTH_CLOCK = 5.f;
};