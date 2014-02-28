#pragma once

#include <list>
#include "IEntity.h"

class Water : public IEntity
{
public:
	Water(void);
	void doAction(IEntity* other);
	void getAction(IEntity* other);
	void draw(sf::RenderTexture *, sf::Shader &);
	void draw(sf::RenderTexture *);
	void loadAnimation(std::string const & string_anim, float speed);
	Type getType() const;
	void update(Map &);
	~Water(void);
private:
};

