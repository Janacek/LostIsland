#pragma once

#include <list>
#include "IEntity.h"

#include "Chunk.h"

#include <iostream>


class Tree : public IEntity
{
public:
	Tree();
	virtual void doAction(IEntity* other);
	virtual void getAction(IEntity* other);
	void loadAnimation(std::string const & string_anim, float speed);
	virtual void draw(sf::RenderTexture *, sf::Shader &);
	virtual void draw(sf::RenderTexture *);
	virtual void update(Map &);
	virtual Type getType() const;
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
	std::list<std::pair<float, float>> getPath() const { return this->_path; };
	sf::FloatRect getBoxCollider() const { return sf::FloatRect(0.f, 0.f, 0.f, 0.f); };
	
	//sf::Rect & getCollisionBox(void);

protected:
	std::list<std::pair<float, float> > _path;
	int				_damages;
	int				_duration;
	sf::Vector2f	_position;
	bool			_isCut;
	bool			_isHarvested;
};