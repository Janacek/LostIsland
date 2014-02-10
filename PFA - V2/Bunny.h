#pragma once

#include "IEntity.h"
#include "Animation.h"
#include "ImageSingleton.h"
#include "Camera.h"
#include "Chunk.h"
#define TIMESTOP 3
#define IT_BEF_STOP 20

class Bunny : public IEntity
{
public:
	Bunny();
	Bunny(sf::Vector2f &, int, Camera *);
	virtual ~Bunny();

	void doAction(IEntity *);
	void getAction(IEntity *);
	void loadAnimation(std::string const &, float);
	void draw();
	void update(Map &map);
	void setPath(std::list<std::pair<float, float>> &);
	void setPosition(sf::Vector2f &);
	sf::Vector2f getPosition() const;
	int getDamage(void) const;
	Type getType() const;
	bool getIsMoving() const;
	float getPathToGo() const;
	void setPathToGo(float f);
	void moveToNextWP();
	void addToPathToGo(float f);

	bool						const getSelected() const{ return true; }
	bool const getIsPathFound() const;
	void setIsPathFound(bool);
	bool getIsStopped() const{ return _isStop; }


private:
	Animation				*_anim;
	Camera					*_camera;
	bool					_isMoving;
	bool					_hasAPath;
	bool					_isPathFound;
	bool					_isStop;
	// Bunny pathfinding
	sf::Clock				_mvtClock;
	float					_speed;
	double					_oldDtMvt;
	double					_oldTime;
	int						_iterPath;

	std::list<std::pair<float, float> >	_path;
	float								_pathToGo; // /!\ il doit partir a 1
	// Bunny's position
	sf::RectangleShape		_rect;
	sf::Vector2f			_position;
	sf::Vector2f			_posDisp;

	// Bunny's life
	int						_life;

};