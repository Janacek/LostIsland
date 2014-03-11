#pragma once

#include "AEntity.h"

class Mushroom : public AEntity
{
public:
	Mushroom();
	virtual void doAction(AEntity* other);
	virtual void getAction(AEntity* other);
	virtual void loadAnimation(std::string const & string_anim, float speed);
	virtual void draw(sf::RenderTexture *, sf::Shader &);
	virtual void draw(sf::RenderTexture *);
	virtual Type getType() const;
	~Mushroom(void);
	void update(Map &);

	virtual std::string &serialize() const;
	virtual void deserialize(std::ifstream &) throw (MyException);

private:
	bool			_picked;
};