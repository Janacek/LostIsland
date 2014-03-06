#include "Tree.h"
#include "Singleton.h"
#include "ImageManager.h"

std::string &Tree::serialize() const
{
	std::string toto;
	return (toto);
}

void Tree::deserialize(std::ifstream &) throw (MyException)
{
	//load
}

Tree::Tree()
: AEntity(0.f, false, sf::Vector2f(0, 0), 0, sf::FloatRect(0, 0, 0, 0), 0)
{
	_duration = 100;
	_isCut = false;
	_isHarvested = false;
}

void Tree::doAction(AEntity* other)
{
	//L'arbre ne fait rien
}


void Tree::getAction(AEntity* other)
{

}

void Tree::update(Map &map)
{
}

void Tree::loadAnimation(std::string const & string_anim, float speed)
{
}

Type Tree::getType() const
{
	return TREE;
}

void Tree::draw(sf::RenderTexture *, sf::Shader &)
{

}

void Tree::draw(sf::RenderTexture *)
{

}
