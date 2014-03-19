#include "Mushroom.h"
#include "ImageManager.h"
#include "ShadersManager.h"
#include "Player.h"

std::string &Mushroom::serialize() const
{
	std::string toto;
	return (toto);
}

void Mushroom::deserialize(std::ifstream &) throw (MyException)
{
	//load
}

Mushroom::Mushroom()
: AEntity(0.f, false, sf::Vector2f(0, 0), 0, sf::FloatRect(0, 0, 0, 0), 0)
{
	_picked = false;
}

void Mushroom::doAction(AEntity *other)
{
	// do action
	if (other)
	{
		Player *player = dynamic_cast<Player *>(other);
		player->eat(5);
		if (std::rand() % 2)
			player->_isSick = true;
	}
}

void Mushroom::getAction(AEntity *other)
{
	if (!_picked)
	{
		_isActionOver = true;
		_picked = true;
		_isDead = true;
		Player *player = dynamic_cast<Player *>(other);
		player->addEntityInInventory(new Mushroom);
	}
}

void Mushroom::loadAnimation(std::string const &, float)
{

}

void Mushroom::update(Map &)
{

}

void Mushroom::draw(sf::RenderTexture *tex, sf::Shader &)
{
	sf::Sprite tmp;
	tmp.setTexture((*ImageManager::getInstance().get(PICKABLE_MUSHROOM)));
	tmp.setPosition(_position.x, _position.y + 20);
	ShadersManager::getInstance().get(BLOOM)->setParameter("RenderedTexture", sf::Shader::CurrentTexture);

	tex->draw(tmp, ShadersManager::getInstance().get(BLOOM));
}

void Mushroom::draw(sf::RenderTexture *tex)
{
	sf::Sprite tmp;
	tmp.setTexture((*ImageManager::getInstance().get(PICKABLE_MUSHROOM)));
	tmp.setPosition(_position.x, _position.y + 20);
	tex->draw(tmp);
}

Type Mushroom::getType() const
{
	return MUSHROOM;
}

Mushroom::~Mushroom(void)
{
}
