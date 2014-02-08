#pragma once

#include <list>
#include "IEntity.h"

class Water : public IEntity
{
public:
	Water(void);
	void doAction(IEntity* other);
	void getAction(IEntity* other);
	void draw();
	void setPosition(sf::Vector2f &pos);
	void loadAnimation(std::string const & string_anim, float speed);
	bool getIsMoving() const { return false; }
	float getPathToGo() const { return 0.f; }
	void setPathToGo(float f) { (void)f; }
	void addToPathToGo(float f) { (void)f; }
	bool const getSelected() const{ return true; }
	bool const getIsPathFound() const { return false; }
	void setIsPathFound(bool n) { (void)n; }

	int getDamage(void) const;
	Type getType() const;
	void update(Map &);
	~Water(void);
	void setPath(std::list<std::pair<float, float> > &path);

	sf::Vector2f  getPosition() const;

	//sf::Rect & getCollisionBox(void);

private:
	std::list<std::pair<float, float> > _path;
	sf::Vector2f			_pos;
};

