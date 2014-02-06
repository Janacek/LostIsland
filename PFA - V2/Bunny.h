#pragma once

#include	"IEntity.h"
#include "Animation.h"
#include "ImageSingleton.h"
#include "Camera.h"
#include "Chunk.h"

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
	void update();
	void setPath(std::list<std::pair<float, float>> &);
	void setPosition(sf::Vector2f &);
	sf::Vector2f getPosition() const;
	int getDamage(void) const;
	Type getType() const;

private:
	Animation				*_anim;
	Camera					*_camera;

	// Bunny pathfinding
	std::list<std::pair<float, float> >	_path;

	// Bunny's position
	sf::RectangleShape		_rect;
	sf::Vector2f			_position;
	sf::Vector2f			_posDisp;

	// Bunny's life
	int						_life;

};