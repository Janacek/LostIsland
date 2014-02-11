#pragma once

#include <list>
#include "IEntity.h"

class Wood : public IEntity
{
public:
	Wood(void);
	virtual void doAction(IEntity* other);
	virtual void getAction(IEntity* other);
	virtual void loadAnimation(std::string const & string_anim, float speed);
	virtual int getDamage(void) const;
	virtual void draw(sf::RenderTexture *);
	virtual void setPosition(sf::Vector2f &pos);
	virtual bool getIsMoving() const { return false; }
	virtual float getPathToGo() const { return 0.f; }
	virtual void setPathToGo(float f) { (void)f; }
	virtual void addToPathToGo(float f) { (void)f; }
	virtual bool const getSelected() const{ return true; }
	bool const getIsPathFound() const { return false; }
	void setIsPathFound(bool n) { (void)n; }
	virtual Type getType() const;
	~Wood(void);
	void update(Map &);
	virtual void setPath(std::list<std::pair<float, float> > &path);
	virtual bool getIsStopped() const{ return false; }

	virtual sf::Vector2f  getPosition() const;

	//sf::Rect & getCollisionBox(void);

private:
	std::list<std::pair<float, float> > _path;
	sf::Vector2f _pos;

};

