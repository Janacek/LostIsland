#pragma once

#include <list>
#include "AEntity.h"

class Food :public AEntity
{
public:
	Food(void);
	void doAction(AEntity* other);
	void getAction(AEntity* other);
	void update(Map &);
	void loadAnimation(std::string const & string_anim, float speed);
	void draw(sf::RenderTexture *, sf::Shader &);
	void draw(sf::RenderTexture *);
	Type getType() const;
	~Food(void);
private:
};

