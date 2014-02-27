#pragma once

#include "IEntity.h"
#include "Animation.h"
#include "AnimatedSprite.h"

class Campfire : public IEntity
{
public:
	Campfire(Camera *);
	virtual void doAction(IEntity* other);
	virtual void getAction(IEntity* other);
	virtual void loadAnimation(std::string const & string_anim, float speed);
	virtual int getDamage(void) const;
	virtual void draw(sf::RenderTexture *, sf::Shader &);
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
	virtual ~Campfire(void);
	void update(Map &);
	virtual void setPath(std::list<std::pair<float, float> > &path);
	virtual bool getIsStopped() const{ return false; }
	virtual bool getIsAMovingEntity() const{ return false; }
	virtual std::list<std::pair<float, float>> getPath() const { return this->_path; };
	virtual sf::FloatRect getBoxCollider() const { return sf::FloatRect(0.f, 0.f, 0.f, 0.f); };
	virtual sf::Vector2f  getPosition() const;

	//sf::Rect & getCollisionBox(void);

private:
	std::list<std::pair<float, float> > _path;
	sf::Vector2f						_pos;
	sf::Vector2f						_posDisp;

	Animation							*_fireAnim;
	Animation							*_curAnim;
	AnimatedSprite						*_animatedSprite;
	Camera								*_camera;
};