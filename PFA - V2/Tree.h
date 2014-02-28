#pragma once

#include <list>
#include "AEntity.h"

#include "Chunk.h"

#include <iostream>


class Tree : public AEntity
{
public:
	Tree();
	virtual void doAction(AEntity* other);
	virtual void getAction(AEntity* other);
	void loadAnimation(std::string const & string_anim, float speed);
	virtual void draw(sf::RenderTexture *, sf::Shader &);
	virtual void draw(sf::RenderTexture *);
	virtual void update(Map &);
	virtual Type getType() const;
protected:
	int				_duration;
	bool			_isCut;
	bool			_isHarvested;
};