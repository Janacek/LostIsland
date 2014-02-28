#pragma once

#include <list>
#include "IEntity.h"

class Food :public IEntity
{
public:
	Food(void);
	void doAction(IEntity* other);
	void getAction(IEntity* other);
	void update(Map &);
	void loadAnimation(std::string const & string_anim, float speed);
	void draw(sf::RenderTexture *, sf::Shader &);
	void draw(sf::RenderTexture *);
	Type getType() const;
	~Food(void);
private:
};

