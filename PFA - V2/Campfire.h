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
	virtual void draw(sf::RenderTexture *, sf::Shader &);
	virtual void draw(sf::RenderTexture *);
	virtual Type getType() const;
	virtual ~Campfire(void);
	void update(Map &);

	//sf::Rect & getCollisionBox(void);

private:
	std::list<std::pair<float, float> > _path;
	sf::Vector2f						_posDisp;

	Animation							*_fireAnim;
	Animation							*_curAnim;
	AnimatedSprite						*_animatedSprite;
	Camera								*_camera;
};