#pragma once

#include				"Singleton.h"

class Animation
{
public:
	Animation(sf::Texture *image, int nbFrame, int nbAnimation, float time);

	void					setFrameTime(float temps);
	float					getFrameTime() const;
	bool					setAnimation(int animation);
	int					getActualAnimation() const;
	int					getActualFrame() const;
	void					setLoop(bool boucle);
	bool					getLoop() const;
	void					play();
	void					pause();
	void					stop();
	bool					isPaused() const;
	bool					isStopped() const;
	void					show(sf::Vector2f position = sf::Vector2f(0, 0));

	sf::Vector2f			GetHeightPerso() const;

private:
	bool					setFrame(int frame);
	void					animate();

	
	sf::Sprite			_sprite;
	int					_nbAnimation;
	int					_actualAnimation;
	int					_nbFrame;
	int					_actualFrame;
	float					_timeFrame;
	float					_timeLeft;
	bool					_pause;
	bool					_loop;
};

