#pragma once

#include <list>
#include "IEntity.h"
#include "Singleton.h"
#include "ImageSingleton.h"
#include "ShadersManager.h"
#include "Chunk.h"

#include <iostream>


class Rock : public IEntity
{
public:
	virtual void doAction(IEntity* other);
	virtual void getAction(IEntity* other);
	void loadAnimation(std::string const & string_anim, float speed);
	virtual void draw(sf::RenderTexture *, sf::Shader &);
	virtual void draw(sf::RenderTexture *);
	virtual void update(Map &);
	Type getType() const;
	int getDamage(void) const;
	bool getIsMoving() const { return false; }
	void setPath(std::list<std::pair<float, float> >&  path);
	float getPathToGo() const { return 0.f; }
	void setPathToGo(float f) { (void)f; }
	void addToPathToGo(float f) { (void)f; }
	bool const getSelected() const{ return true; }
	bool const getIsPathFound() const { return false; }
	void setIsPathFound(bool n) { (void)n; }
	bool getIsStopped() const{ return false; }

	void setPosition(sf::Vector2f &);
	sf::Vector2f  getPosition() const;
	bool getIsAMovingEntity() const{ return false; }


	//sf::Rect & getCollisionBox(void);

protected:
	std::list<std::pair<float, float> > _path;
	int				_damages;
	sf::Vector2f	_position;
};