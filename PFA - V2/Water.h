#pragma once

#include <list>
#include "AEntity.h"

class Water : public AEntity
{
public:
	Water(void);
	void doAction(AEntity* other);
	void getAction(AEntity* other);
	void draw(sf::RenderTexture *, sf::Shader &);
	void draw(sf::RenderTexture *);
	void loadAnimation(std::string const & string_anim, float speed);
	Type getType() const;
	void update(Map &);
	~Water(void);
private:
};

