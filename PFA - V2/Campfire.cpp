#include "Campfire.h"
#include "Player.h"
#include "ShadersManager.h"

Campfire::Campfire(Camera *camera)
: _camera(camera), AEntity(0.f, false, sf::Vector2f(0, 0), 0, sf::FloatRect(0, 0, 0, 0), 0)
{
	loadAnimation("./Media/images/campfire.png", 0.1f);
}

void Campfire::doAction(AEntity *other)
{
	//do something
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

	sf::Time t = sf::seconds(dt);;
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
	//_posDisp.x = ((_position.x - _camera->_position.x) * Chunk::SIZE_OF_CELL);
	//_posDisp.y = ((_position.y - _camera->_position.y) * Chunk::SIZE_OF_CELL);

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