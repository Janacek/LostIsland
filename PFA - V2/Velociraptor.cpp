#include "Velociraptor.h"

Velociraptor::Velociraptor(sf::Vector2f &position, int life, Camera *cam)
: Dinosaur(position, life, cam)
{
	loadAnimation("Media/images/velociraptor.png", 0.1f);
}

Velociraptor::~Velociraptor()
{

}

void Velociraptor::loadAnimation(std::string const &string_anim, float time)
{
	sf::Texture *imgAnim = new sf::Texture;
	sf::Color color(0, 255, 0);
	if (!imgAnim->loadFromFile(string_anim))
		std::cerr << "image non charge" << std::endl;
	sf::Image img_tmp = imgAnim->copyToImage();
	img_tmp.createMaskFromColor(color);
	imgAnim->loadFromImage(img_tmp);


	_walkDown = new Animation();
	_walkDown->setSpriteSheet(*imgAnim);
	_walkDown->addFrame(sf::IntRect(214, 34, 32, 63));
	_walkDown->addFrame(sf::IntRect(247, 34, 32, 63));
	_walkDown->addFrame(sf::IntRect(279, 34, 32, 63));
	_walkDown->addFrame(sf::IntRect(312, 34, 32, 63));
	_walkDown->addFrame(sf::IntRect(344, 34, 32, 63));
	_walkDown->addFrame(sf::IntRect(376, 34, 32, 63));
	
	_walkLeft = new Animation();
	_walkLeft->setSpriteSheet(*imgAnim);
	_walkLeft->addFrame(sf::IntRect(442, 330, 79, 51));
	_walkLeft->addFrame(sf::IntRect(357, 330, 79, 51));
	_walkLeft->addFrame(sf::IntRect(272, 330, 79, 51));
	_walkLeft->addFrame(sf::IntRect(189, 330, 79, 51));
	_walkLeft->addFrame(sf::IntRect(104, 330, 79, 51));
	_walkLeft->addFrame(sf::IntRect(18, 330, 79, 51));

	_walkRight = new Animation();
	_walkRight->setSpriteSheet(*imgAnim);
	_walkRight->addFrame(sf::IntRect(4, 174, 79, 51));
	_walkRight->addFrame(sf::IntRect(89, 174, 79, 51));
	_walkRight->addFrame(sf::IntRect(173, 174, 79, 51));
	_walkRight->addFrame(sf::IntRect(257, 174, 79, 51));
	_walkRight->addFrame(sf::IntRect(342, 174, 79, 51));
	_walkRight->addFrame(sf::IntRect(428, 174, 79, 51));

	_walkUp = new Animation();
	_walkUp->setSpriteSheet(*imgAnim);
	_walkUp->addFrame(sf::IntRect(4, 35, 32, 63));
	_walkUp->addFrame(sf::IntRect(41, 35, 32, 63));
	_walkUp->addFrame(sf::IntRect(76, 35, 32, 63));
	_walkUp->addFrame(sf::IntRect(110, 35, 32, 63));
	_walkUp->addFrame(sf::IntRect(145, 35, 32, 63));
	_walkUp->addFrame(sf::IntRect(180, 35, 32, 63));

	_attackLeft = new Animation();
	_attackLeft->setSpriteSheet(*imgAnim);
	_attackLeft->addFrame(sf::IntRect(615, 319, 80, 68));
	_attackLeft->addFrame(sf::IntRect(529, 319, 80, 68));
	
	_attackRight = new Animation();
	_attackRight->setSpriteSheet(*imgAnim);
	_attackRight->addFrame(sf::IntRect(538, 171, 80, 68));
	_attackRight->addFrame(sf::IntRect(624, 171, 80, 68));

	_attackUp = new Animation();
	_attackUp->setSpriteSheet(*imgAnim);
	_attackUp->addFrame(sf::IntRect(537, 35, 28, 63));
	_attackUp->addFrame(sf::IntRect(570, 35, 28, 63));

	_attackDown = new Animation();
	_attackDown->setSpriteSheet(*imgAnim);
	_attackDown->addFrame(sf::IntRect(604, 34, 28, 63));
	_attackDown->addFrame(sf::IntRect(637, 34, 28, 63));

	_animatedSprite = new AnimatedSprite(sf::seconds(0.1), true, false);
	_curAnim = _walkDown;


	_animatedSprite->play(*_curAnim);
}