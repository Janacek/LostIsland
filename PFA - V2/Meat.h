#pragma once

#include <list>
#include "AEntity.h"

class Meat :public AEntity
{
public:
	Meat(void);
	void doAction(AEntity* other);
	void getAction(AEntity* other);
	void update(Map &);
	void loadAnimation(std::string const & string_anim, float speed);
	void draw(sf::RenderTexture *, sf::Shader &);
	void draw(sf::RenderTexture *);
	Type getType() const;
	~Meat(void);

	virtual std::string &serialize() const;
	virtual void deserialize(std::ifstream &) throw (MyException);
private:
	int				_value;
};

