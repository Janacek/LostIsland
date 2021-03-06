#include "Rock.h"
#include "Player.h"
#include "Flint.h"

std::string &Rock::serialize() const
{
	std::string toto;
	return (toto);
}

void Rock::deserialize(std::ifstream &) throw (MyException)
{
	//load
}

Rock::Rock()
: AEntity(0.f, false, sf::Vector2f(0, 0), 0, sf::FloatRect(0, 0, 0, 0), 0)
{
	_duration = 200;
	_isMined = false;
}

void Rock::doAction(AEntity* other)
{
	if (other)
	{
		Player *player = dynamic_cast<Player *>(other);
		player->addEntityInInventory(new Rock);
	}
}


void Rock::getAction(AEntity* other)
{
	_duration -= other->getDamage();
	if (_duration <= 0 && !_isMined)
	{
		try // si c'est un player
		{
			_isActionOver = true;
			Player *player = dynamic_cast<Player *>(other);
			if (std::rand() % 10 == 0)
				player->addEntityInInventory(new Flint);
			player->addEntityInInventory(this);
		}
		catch (std::bad_cast ex)
		{
			std::cout << "Cas non g�r�. C'est un animal qui attaque l'arbre." << std::endl;
		}
		_isMined = true;
	}
}

void Rock::update(Map &map)
{

}

void Rock::loadAnimation(std::string const & string_anim, float speed)
{
}

Type Rock::getType() const
{
	return ROCK;
}

void Rock::draw(sf::RenderTexture *tex, sf::Shader &shader)
{
	sf::Sprite tmp;
	if (!_isMined)
		tmp.setTexture((*ImageManager::getInstance().get(ROCK)));
	else
		tmp.setTexture((*ImageManager::getInstance().get(ROCK_BROKEN)));
	tmp.setPosition(_position.x, _position.y + 20);
	ShadersManager::getInstance().get(BLOOM)->setParameter("RenderedTexture", sf::Shader::CurrentTexture);

	tex->draw(tmp, ShadersManager::getInstance().get(BLOOM));
}

void Rock::draw(sf::RenderTexture *tex)
{
	sf::Sprite tmp;
	if (!_isMined)
		tmp.setTexture((*ImageManager::getInstance().get(ROCK)));
	else
		tmp.setTexture((*ImageManager::getInstance().get(ROCK_BROKEN)));
	tmp.setPosition(_position.x, _position.y + 20);
	tex->draw(tmp);
}


/*sf::Rect & Rock::getCollisionBox(void)
{
}*/
