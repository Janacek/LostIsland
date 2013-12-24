#include "ImageSingleton.h"
#include <iostream>

ImageSingleton ImageSingleton::m_instance=ImageSingleton();

/// <summary>
/// Constructeur du singleton contenant les textures. Il faut appeler la méthode start pour load toutes les textures 
/// </summary>
ImageSingleton::ImageSingleton()
{
	
}

void ImageSingleton::start()
{
	this->load(FOOD, "./food.png");
	this->load(WATER, "./water.png");
	this->load(WOOD, "./wood.png");
	this->load(SABLE, "./sable.png");
	this->load(LAC, "./lac.png");
}

void ImageSingleton::load(Type id, const std::string& filename)
{
	sf::Texture *texture = new sf::Texture();
	if (texture->loadFromFile(filename) == false)
		std::cout << "ERROR IN LOAD " << std::endl;
	this->_mapTexture.insert(std::make_pair(id, std::move(texture)));
}

sf::Texture *ImageSingleton::get(Type id)
{
	auto found = this->_mapTexture.find(id);
	return found->second;
}

ImageSingleton& ImageSingleton::getInstance()
{
	return m_instance;
}

ImageSingleton::~ImageSingleton()
{

}