#include "Campfire.h"
#include "Player.h"

Campfire::Campfire()
{
	_pos = sf::Vector2f(0, 0);
	_id = IEntityId++;
	loadAnimation("./Media/images/campfire.pnge", 0.1f)
}

void Campfire::doAction(IEntity *other)
{
//do something
}

void Campfire::getAction(IEntity *other)
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
	_fireAnim->addFrame(sf::IntRect(0, 0, 50, 50));
	_fireAnim->addFrame(sf::IntRect(50, 0, 50, 50));
	_fireAnim->addFrame(sf::IntRect(100, 0, 50, 50));
	_fireAnim->addFrame(sf::IntRect(150, 0, 50, 50));
	_fireAnim->addFrame(sf::IntRect(200, 0, 50, 50));

	_animatedSprite = new AnimatedSprite(sf::seconds(0.1), true, false);
	_curAnim = _fireAnim;


	_animatedSprite->play(*_curAnim);
}

void Campfire::update(Map &map)
{

}

void Campfire::draw(sf::RenderTexture *, sf::Shader &)
{

}

void Campfire::draw(sf::RenderTexture *)
{

}

void Campfire::setPosition(sf::Vector2f &pos)
{
	_pos = pos;
}

int Campfire::getDamage() const
{
	return 0;
}

Type Campfire::getType() const
{
	return CAMPFIRE;
}

sf::Vector2f Campfire::getPosition() const
{
	return _pos;
}

void Campfire::setPath(std::list<std::pair<float, float>> &path)
{
	_path = path;
}

Campfire::~Campfire()
{

}