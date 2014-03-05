#pragma once

#include "AEntity.h"

class Sword : public AEntity
{
public:
	Sword();
	virtual void doAction(AEntity* other);
	virtual void getAction(AEntity* other);
	virtual void loadAnimation(std::string const & string_anim, float speed);
	virtual void draw(sf::RenderTexture *, sf::Shader &);
	virtual void draw(sf::RenderTexture *);
	virtual Type getType() const;
	~Sword(void);
	void update(Map &);
	virtual std::string &serialize() const;
	virtual void deserialize(std::ifstream &) throw (MyException);
};