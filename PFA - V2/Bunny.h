#pragma once

#include "AEntity.h"
#include "Animation.h"
#include "AnimatedSprite.h"
#include "Camera.h"

#define TIMESTOP 3
#define IT_BEF_STOP 20

class Bunny : public AEntity
{
public:
	Bunny(sf::Vector2f &, int, Camera *);
	virtual ~Bunny();

	void								doAction(AEntity *);
	void								getAction(AEntity *);
	void								loadAnimation(std::string const &, float);
	void								draw(sf::RenderTexture *);
	void								draw(sf::RenderTexture *, sf::Shader &);
	void								update(Map &map);
	Type								getType() const;
	void								moveToNextWP();

private:
	void								changeAnimation(sf::Vector2f&, std::pair<float, float>);

	Animation							*_anim;
	Camera								*_camera;
	bool								_hasAPath;
	bool								_firstPath;
	// Bunny pathfinding
	sf::Clock							_mvtClock;
	float								_speed;
	double								_oldDtMvt;
	double								_oldTime;
	int									_iterPath;

	std::list<std::pair<float, float> >	_originalPath;
	// Bunny's position
	sf::RectangleShape					_rect;
	sf::Vector2f						_posDisp;

	// Bunny's life

	Animation							*_walkUp;
	Animation							*_walkDown;
	Animation							*_walkLeft;
	Animation							*_walkRight;
	Animation							*_curAnim;
	AnimatedSprite						*_animatedSprite;
};