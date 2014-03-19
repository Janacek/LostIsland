#pragma once

#include "AEntity.h"
#include "Animation.h"
#include "AnimatedSprite.h"
#include "Camera.h"
#include "SFML\Audio\Sound.hpp"
#include "SFML\Audio\SoundBuffer.hpp"

#define TIMESTOP 3
#define IT_BEF_STOP 20

class HarmfullAnimal : public AEntity
{
public:
	HarmfullAnimal(sf::Vector2f &, int, Camera *);
	virtual ~HarmfullAnimal();

	void								doAction(AEntity *);
	void								getAction(AEntity *);
	virtual void						loadAnimation(std::string const &, float);
	void								draw(sf::RenderTexture *);
	void								draw(sf::RenderTexture *, sf::Shader &);
	void								update(Map &map);
	virtual Type						getType() const;
	void								moveToNextWP();
	sf::FloatRect						getBoxCollider() const;

	virtual std::string &serialize() const;
	virtual void deserialize(std::ifstream &) throw (MyException);

protected:
	void								changeAnimation(sf::Vector2f&, std::pair<float, float>);
	sf::Vector2i				const	diffDist(sf::Vector2f&first, sf::Vector2f&second);
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
	sf::SoundBuffer						_screamBuffer;
	sf::Sound							_scream;
	std::list<std::pair<float, float> >	_originalPath;
	// Bunny's position
	sf::RectangleShape					_rect;


	// Bunny's life

	Animation							*_walkUp;
	Animation							*_walkDown;
	Animation							*_walkLeft;
	Animation							*_walkRight;
	Animation							*_attackLeft;
	Animation							*_attackRight;
	Animation							*_attackDown;
	Animation							*_attackUp;

	Animation							*_curAnim;
	AnimatedSprite						*_animatedSprite;
};