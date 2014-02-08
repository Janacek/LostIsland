#include <iostream>
#include "Animation.h"

Animation::Animation(sf::Texture *image, int nbFrame, int nbAnimation, float time) :
_sprite(*image), _nbAnimation(nbAnimation), _nbFrame(nbFrame), _timeFrame(time), _timeLeft(time)
{
	_pause = false;
	_loop = true;
	setAnimation(0);
	setFrame(0);
	//int					_nbAnimation;
	
}

void Animation::show(sf::Vector2f position)
{
	animate();

	int largeurFrame(_sprite.getTexture()->getSize().x / (_nbFrame + 1));
	int hauteurFrame(_sprite.getTexture()->getSize().y / (_nbAnimation + 1));

	int left(largeurFrame * (_actualFrame));
	int top(hauteurFrame * (_actualAnimation));
	sf::IntRect subRect(left, top, largeurFrame, hauteurFrame);
	sf::Image test;

	_sprite.setTextureRect(subRect);

	_sprite.setPosition(position);

	Singleton::getInstance()._window->draw(_sprite);

}

bool Animation::setFrame(int frame)
{
	if (frame >= 0 && frame <= _nbFrame)
	{
		_actualFrame = frame;
		return true;
	}
	return false;
}

void Animation::animate()
{
	if (!_pause)
	{
		_timeLeft -= Singleton::getInstance()._animClock->getElapsedTime().asSeconds();
		
		if (_timeLeft <= 0.f)
		{
			_timeLeft = _timeFrame;

			if (!setFrame(getActualFrame() + 1))
			{
				if (_loop)
					setFrame(0);
				else
					stop();
			}
		}
	}
}

bool Animation::setAnimation(int animation)
{
	if (animation >= 0 && animation <= _nbAnimation)
	{
		_actualAnimation = animation;
		return true;
	}
	return false;
}

void Animation::setFrameTime(float temps)
{
	_timeFrame = temps;
}

float Animation::getFrameTime() const
{
	return _timeLeft;
}

int Animation::getActualAnimation() const
{
	return _actualAnimation;
}

int Animation::getActualFrame() const
{
	return _actualFrame;
}

void Animation::setLoop(bool loop)
{
	_loop = loop;
}

bool Animation::getLoop() const
{
	return _loop;
}

void Animation::play()
{
	
	_pause = false;
}

void Animation::pause()
{
	_pause = true;
}

void Animation::stop()
{
	setFrame(0);
	_timeLeft = _timeFrame;
	_pause = true;
}

bool Animation::isPaused() const{
	return _pause;
}

bool Animation::isStopped() const{
	return (_pause && (getActualFrame() == 0) && (_timeLeft == _timeFrame));
}

sf::Vector2f Animation::GetHeightPerso() const{
	return sf::Vector2f(static_cast<float>(_sprite.getTexture()->getSize().x / (_nbFrame + 1)), static_cast<float>(_sprite.getTexture()->getSize().y / (_nbFrame + 1)));
}
