#pragma once

#include <list>
#include "AEntity.h"
#include "Singleton.h"
#include "ImageManager.h"
#include "ShadersManager.h"
#include "Chunk.h"

#include <iostream>


class Rock : public AEntity
{
public:
	Rock();
	virtual void doAction(AEntity* other);
	virtual void getAction(AEntity* other);
	void loadAnimation(std::string const & string_anim, float speed);
	virtual void draw(sf::RenderTexture *, sf::Shader &);
	virtual void draw(sf::RenderTexture *);
	virtual void update(Map &);
	Type getType() const;

	virtual std::string &serialize() const;
	virtual void deserialize(std::ifstream &) throw (MyException);
protected:
	int				_duration;
	bool			_isMined;
};