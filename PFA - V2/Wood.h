#pragma once

#include <list>
#include "IEntity.h"

class Wood : public IEntity
{
public:
	Wood(void);
	virtual void doAction(IEntity* other);
	virtual void getAction(IEntity* other);
	virtual void Animate(std::string const & string_anim);
	virtual int getDamage(void) const;
	virtual void draw();
	virtual void setPosition(sf::Vector2f &pos);
	virtual Type getType() const;
	~Wood(void);
	virtual void setPath(std::list<std::pair<float, float> > &path);

	virtual sf::Vector2f  getPosition() const;

	//sf::Rect & getCollisionBox(void);

private:
	std::list<std::pair<float, float> > _path;
	sf::Vector2f _pos;

};

