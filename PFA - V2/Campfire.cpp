#include "Campfire.h"
#include "Player.h"
#include "ShadersManager.h"

std::string &Campfire::serialize() const
{
	std::string toto;
	return (toto);
}

void Campfire::deserialize(std::ifstream &) throw (MyException)
{
	//load
}

Campfire::Campfire()
: AEntity(0.f, false, sf::Vector2f(0, 0), 0, sf::FloatRect(0, 0, 0, 0), 0)
{
	loadAnimation("./Media/images/campfire.png", 0.1f);
	_duration = 60;
}

void Campfire::doAction(AEntity *other)
{
	// do action
	if (other)
	{
		Player *player = dynamic_cast<Player *>(other);
		Map * map = player->getMap();
		sf::Vector2f pPos = player->getPosition();
		if (map->getCellMap()[(int)pPos.y + 1][(int)pPos.x]._cellType != Cell::OCEAN &&
			map->getEntityAt((int)pPos.y + 1, (int)pPos.x) == NULL)
			map->setEntityMap(new Campfire, (int)pPos.y + 1, (int)pPos.x);
		else if (map->getCellMap()[(int)pPos.y][(int)pPos.x + 1]._cellType != Cell::OCEAN &&
			map->getEntityAt((int)pPos.y, (int)pPos.x + 1) == NULL)
			map->setEntityMap(new Campfire, (int)pPos.y, (int)pPos.x + 1);
		else if (map->getCellMap()[(int)pPos.y][(int)pPos.x - 1]._cellType != Cell::OCEAN &&
			map->getEntityAt((int)pPos.y, (int)pPos.x - 1) == NULL)
			map->setEntityMap(new Campfire, (int)pPos.y, (int)pPos.x - 1);
		else if (map->getCellMap()[(int)pPos.y - 1][(int)pPos.x]._cellType != Cell::OCEAN &&
			map->getEntityAt((int)pPos.y - 1, (int)pPos.x) == NULL)
			map->setEntityMap(new Campfire, (int)pPos.y - 1, (int)pPos.x);
		else
			player->addEntityInInventory(new Campfire);
	}
}

void Campfire::getAction(AEntity *other)
{
	//get something
}

void Campfire::loadAnimation(std::string const &string_anim, float speed)
{
	sf::Texture *imgAnim = new sf::Texture;
	if (!imgAnim->loadFromFile(string_anim))
		std::cerr << "image non charge" << std::endl;
	sf::Image img_tmp = imgAnim->copyToImage();
	imgAnim->loadFromImage(img_tmp);

	_fireAnim = new Animation();
	_fireAnim->setSpriteSheet(*imgAnim);
	_fireAnim->addFrame(sf::IntRect(0, 0, 32, 32));
	_fireAnim->addFrame(sf::IntRect(32, 0, 32, 32));
	_fireAnim->addFrame(sf::IntRect(64, 0, 32, 32));
	_fireAnim->addFrame(sf::IntRect(96, 0, 32, 32));
	_fireAnim->addFrame(sf::IntRect(128, 0, 32, 32));

	_animatedSprite = new AnimatedSprite(sf::seconds(speed), true, false);
	_curAnim = _fireAnim;


	_animatedSprite->play(*_curAnim);
}

void Campfire::update(Map &map)
{
	double dt = 0;
	double time;

	time = _mvtClock.getElapsedTime().asSeconds();
	dt = time - _oldDtMvt;
	_oldDtMvt = time;

	_animatedSprite->play(*_curAnim);

	_duration -= dt;

	if (_duration <= 0)
		_duration = 0;

	sf::Time t = sf::seconds(dt);
	_animatedSprite->update(t);
}

void Campfire::draw(sf::RenderTexture *tex, sf::Shader &)
{
	_animatedSprite->setPosition(_position);
	ShadersManager::getInstance().get(BLOOM)->setParameter("RenderedTexture", sf::Shader::CurrentTexture);

	tex->draw(*_animatedSprite, ShadersManager::getInstance().get(BLOOM));
}

void Campfire::draw(sf::RenderTexture *tex)
{
	_animatedSprite->setPosition(_position);
	tex->draw(*_animatedSprite);
}

Type Campfire::getType() const
{
	return CAMPFIRE;
}

Campfire::~Campfire()
{

}