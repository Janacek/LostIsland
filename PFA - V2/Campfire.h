#pragma once

#include "AEntity.h"
#include "Animation.h"
#include "AnimatedSprite.h"

class Campfire : public AEntity
{
public:
	Campfire(Camera *);
	virtual void doAction(AEntity* other);
	virtual void getAction(AEntity* other);
	virtual void loadAnimation(std::string const & string_anim, float speed);
	virtual void draw(sf::RenderTexture *, sf::Shader &);
	virtual void draw(sf::RenderTexture *);
	virtual Type getType() const;
	virtual ~Campfire(void);
	void update(Map &);

	virtual std::string &serialize() const;
	virtual void deserialize(std::ifstream &) throw (MyException);
	//sf::Rect & getCollisionBox(void);

private:
	std::list<std::pair<float, float> > _path;
	sf::Vector2f						_posDisp;

	Animation							*_fireAnim;
	Animation							*_curAnim;
	AnimatedSprite						*_animatedSprite;
	Camera								*_camera;

	sf::Clock							_mvtClock;
	double								_oldDtMvt;
	double								_oldTime;

	double								_duration;
};