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
	Rock();
	virtual void doAction(IEntity* other);
	virtual void getAction(IEntity* other);
	void loadAnimation(std::string const & string_anim, float speed);
	virtual void draw(sf::RenderTexture *, sf::Shader &);
	virtual void draw(sf::RenderTexture *);
	virtual void update(Map &);
	Type getType() const;
protected:
	int				_duration;
	bool			_isMined;
};