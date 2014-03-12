#include "Velociraptor.h"

Velociraptor::Velociraptor(sf::Vector2f &position, int life, Camera *cam)
: Dinosaur(position, life, cam)
{
	loadAnimation("Media/images/sheep.png", 0.1f);
}

Velociraptor::~Velociraptor()
{

}

void Velociraptor::loadAnimation(std::string const &string_anim, float time)
{
	sf::Texture *imgAnim = new sf::Texture;
	if (!imgAnim->loadFromFile(string_anim))
		std::cerr << "image non charge" << std::endl;
	sf::Image img_tmp = imgAnim->copyToImage();
	imgAnim->loadFromImage(img_tmp);


	_walkDown = new Animation();
	_walkDown->setSpriteSheet(*imgAnim);
	_walkDown->addFrame(sf::IntRect(288, 128, 32, 32));
	_walkDown->addFrame(sf::IntRect(320, 128, 32, 32));
	_walkDown->addFrame(sf::IntRect(352, 128, 32, 32));

	_walkLeft = new Animation();
	_walkLeft->setSpriteSheet(*imgAnim);
	_walkLeft->addFrame(sf::IntRect(288, 160, 32, 32));
	_walkLeft->addFrame(sf::IntRect(320, 160, 32, 32));
	_walkLeft->addFrame(sf::IntRect(352, 160, 32, 32));

	_walkRight = new Animation();
	_walkRight->setSpriteSheet(*imgAnim);
	_walkRight->addFrame(sf::IntRect(288, 192, 32, 32));
	_walkRight->addFrame(sf::IntRect(320, 192, 32, 32));
	_walkRight->addFrame(sf::IntRect(352, 192, 32, 32));

	_walkUp = new Animation();
	_walkUp->setSpriteSheet(*imgAnim);
	_walkUp->addFrame(sf::IntRect(288, 224, 32, 32));
	_walkUp->addFrame(sf::IntRect(320, 224, 32, 32));
	_walkUp->addFrame(sf::IntRect(352, 224, 32, 32));


	_animatedSprite = new AnimatedSprite(sf::seconds(0.1), true, false);
	_curAnim = _walkDown;


	_animatedSprite->play(*_curAnim);
}