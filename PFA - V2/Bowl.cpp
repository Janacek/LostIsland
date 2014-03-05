#include "Bowl.h"

std::string &Bowl::serialize() const
{
	//save
	std::string toto;
	return (toto);
}

void Bowl::deserialize(std::ifstream &) throw (MyException)
{
	// load
}

Bowl::Bowl()
: AEntity(0.f, false, sf::Vector2f(0, 0), 0, sf::FloatRect(0, 0, 0, 0), 0)
{

}

void Bowl::doAction(AEntity *other)
{
	// do action
}

void Bowl::getAction(AEntity *other)
{

}

void Bowl::loadAnimation(std::string const &, float)
{

}

void Bowl::update(Map &)
{

}

void Bowl::draw(sf::RenderTexture *, sf::Shader &)
{

}

void Bowl::draw(sf::RenderTexture *)
{

}

Type Bowl::getType() const
{
	return BOWL;
}

Bowl::~Bowl(void)
{
}
