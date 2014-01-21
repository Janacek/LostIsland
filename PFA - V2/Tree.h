#pragma once

#include <list>
#include "IEntity.h"
#include "Singleton.h"
#include "ImageSingleton.h"
#include <iostream>


class Tree : public IEntity
{
public:
	void doAction(IEntity* other);
	void getAction(IEntity* other);
	void Animate(std::string const & string_anim);
	void draw();
	Type getType() const;
	int getDamage(void) const;
	void setPath(std::list<std::pair<float, float> >&  path);
	
	void setPosition(sf::Vector2f &);
	sf::Vector2f  getPosition() const;
	
	//sf::Rect & getCollisionBox(void);

private:
	std::list<std::pair<float, float> > _path;
	int				_damages;
	sf::Vector2f	_position;


};