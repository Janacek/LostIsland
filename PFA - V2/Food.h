#pragma once

#include <list>
#include "IEntity.h"

class Food :public IEntity
{
public:
	Food(void);
	void doAction(IEntity* other);
	void getAction(IEntity* other);
	void setPath(std::list<std::pair<float, float> >&);
	void update(Map &);
	void loadAnimation(std::string const & string_anim, float speed);
	bool getIsMoving() const { return false; }

	int getDamage(void) const;
	void draw(sf::RenderTexture *, sf::Shader &);
	void draw(sf::RenderTexture *);
	void setPosition(sf::Vector2f &pos);
	sf::Vector2f  getPosition() const;
	
	float getPathToGo() const { return 0.f; }
	void setPathToGo(float f) { (void)f; }
	void addToPathToGo(float f) { (void)f; }
	bool const getSelected() const{ return true; }
	bool const getIsPathFound() const { return false; }
	void setIsPathFound(bool n) { (void)n; }
	Type getType() const;
	bool getIsStopped() const{ return false; }

	~Food(void);
private:
	std::list<std::pair<float, float> > _path;
	sf::Vector2f			_pos;

};

