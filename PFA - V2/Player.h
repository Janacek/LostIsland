#pragma once
#include <vector>
#include <SFGUI/SFGUI.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>
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

class Player : public AEntity
{
public:
	Player(sf::Vector2f &pos, Camera *cam);
	void doAction(AEntity* other);
	void getAction(AEntity* other);
	void drink(Water *);
	void eat(int);
	std::string const &getName() const;
	void setName(std::string const &);
	void loadAnimation(std::string const & string_anim, float speed);
	void draw(sf::RenderTexture *, sf::Shader &);
	void draw(sf::RenderTexture *);
	void setCamPos(sf::Vector2f &); // TMP LE TEMPS QUON AI LA BONNE CLASS

	void move(sf::Vector2f & pos);
	Type getType() const;
	sfg::Box::Ptr getBox();
	sfg::Notebook::Ptr _book;
	bool addEntityInInventory(AEntity *entity);
	bool delEntityInInventory(Type);
	bool delEntityInInventory(AEntity *);
	Compartment	*getCompartment(int index);
	int			posInventory(AEntity *);
	void moveToNextWP();
	void update(Map &);
	void setMap(Map *map) { _map = map; };
	void setInventory(InventoryWindow *inventory) { _inventoryWindow = inventory; };
	Map *getMap() { return _map; };
	void setPath(std::list<std::pair<float, float> > &path);
	void setPosition(sf::Vector2f &pos);
	sf::Vector2i const diffDist(sf::Vector2f&first, sf::Vector2f&second);
	sf::FloatRect getBoxCollider() const;

	virtual std::string &serialize() const;
	virtual void deserialize(std::ifstream &) throw (MyException);

	//TODO : Changer en compartments pour l'inventaire

	sf::Image					_img; //TMP
	// std::vector<AEntity *> _inventary;

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

	void					addInInventoryWindow(AEntity *, int pos);


	Camera						*_camera;

	/*
	** Player pathfinding
	*/
	sf::Clock					_mvtClock;
	float						_oldDtMvt;

	float								_speed;
	bool								_hasAPath;
	bool								_isPathNotFound;
	bool								_isAttacking;
	/*
	** Player's name (could be with miscs)
	*/
	std::string					_name;

	/*
	** Player position
	*/
	sf::RectangleShape			_rect;

	
	unsigned int _sizeInventory;


	/*
	** Player inventory
	*/

	std::vector<Compartment *>	_inventoryPlayer;



	/*
	** Player state
	*/
public:
	float						_water;
	float						_food;
	bool						_isSick;
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
	AEntity						*_objective;
	Type						_target;
	/*
	** Selection of the player.
	*/
public:
	void						doActionOnEntity();
	void						changeMapEntity(Map&);
	void setTarget(Type);
	void						stepsSound();
private:
	bool						_isActionning;
	bool						_isWalking;
	sf::SoundBuffer				_stepsBuffer;
	sf::Sound					_stepts;
	float						_cursorTime;
	void						changeAnimation(sf::Vector2f&, std::pair<float, float>);
	void						changeToActionAnim();
	void						changeToIdleAnim();
	Map							*_map;
	InventoryWindow				*_inventoryWindow;
	float						_timeAttack;
	
public:
	const float					HUNGER_CLOCK = 6.f;
	const float					THIRST_CLOCK = 3.f;
	const float					HEALTH_CLOCK = 5.f;
};