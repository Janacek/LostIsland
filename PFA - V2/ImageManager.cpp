#include "ImageManager.h"
#include <iostream>

ImageManager ImageManager::m_instance=ImageManager();

/// <summary>
/// Constructeur du singleton contenant les textures. Il faut appeler la méthode start pour load toutes les textures 
/// </summary>
ImageManager::ImageManager()
{
	
}

void ImageManager::start()
{
	this->load(FOOD, "./Media/images/food.png");
	this->load(WATER, "./Media/images/water.png");
	this->load(WATER_WALKABLE, "./Media/images/waterWalkable.png");
	this->load(WOOD, "./Media/images/wood.png");
	this->load(SABLE, "./Media/images/sable.png");
	this->load(LAC, "./Media/images/mer.png");
	this->load(GRASS, "./Media/images/grass.png");
	this->load(SAVANNA, "./Media/images/savanna.png");
	this->load(FOREST, "./Media/images/forest.png");
	this->load(SNOW, "./Media/images/snow.png");
	this->load(TREE, "./Media/images/tree.png");
	this->load(CUT_TREE, "./Media/images/cut_tree.png");
	this->load(BUSH, "./Media/images/bushes.png");
	this->load(BUSH_FRUITS, "./Media/images/bush_fruits.png");
	this->load(PALMTREE, "./Media/images/palmtree.png");
	this->load(CUT_PALMTREE, "./Media/images/cut_palmtree.png");
	this->load(BUNNY, "./Media/images/bunny.png");
	this->load(PLAYER_INFOS_BACKGROUND, "./Media/images/woodenPlanks.png");
	this->load(SELECTED_ICON, "./Media/images/selected.png");
	this->load(ROCK, "./Media/images/rock.png");
	this->load(ROCK_BROKEN, "./Media/images/rock_broken.png");
	this->load(DROPS, "./Media/images/drops.png");
	this->load(BERRY, "./Media/images/berry.png");


}

void ImageManager::load(Type id, const std::string& filename)
{
	sf::Texture *texture = new sf::Texture();
	if (texture->loadFromFile(filename) == false)
		std::cout << "ERROR IN LOAD " << std::endl;
	this->_mapTexture.insert(std::make_pair(id, std::move(texture)));
}

sf::Texture *ImageManager::get(Type id)
{
	auto found = this->_mapTexture.find(id);
	return found->second;
}

ImageManager& ImageManager::getInstance()
{
	return m_instance;
}

ImageManager::~ImageManager()
{

}