#pragma once

#include <list>
#include "AEntity.h"

class Grass :public AEntity
{
public:
	Grass(void);
	void doAction(AEntity* other);
	void getAction(AEntity* other);
	void update(Map &);
	void loadAnimation(std::string const & string_anim, float speed);
	void draw(sf::RenderTexture *, sf::Shader &);
	void draw(sf::RenderTexture *);
	Type getType() const;
	~Grass(void);

	virtual std::string &serialize() const;
	virtual void deserialize(std::ifstream &) throw (MyException);
};

