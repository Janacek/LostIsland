#pragma once

#include						<SFML/Window.hpp>
#include						<SFML/Graphics.hpp>

#include <map>
#include <string>
#include <memory>
#include <stdexcept>
#include <cassert>
#include "IEntity.h"

class ImageSingleton
{
public:
	static ImageSingleton& getInstance();

	void start();
	void load(Type id,
		const std::string& filename);
	sf::Texture *get(Type id);
private:
	ImageSingleton(const ImageSingleton&) {};
	static ImageSingleton m_instance;
	ImageSingleton();
	~ImageSingleton();
	std::map<Type,	sf::Texture *> _mapTexture;
};
// 
// class ImageSingleton
// {
// public:
// 	static ImageSingleton& getInstance();
// 
// 	void					start();
//  	sf::Texture				*_waterTexture;
//  	sf::Texture				*_treeTexture;
//  	sf::Texture				*_foodTexture;
//  	sf::Texture				*_woodTexture;
// 
// private:
// 	ImageSingleton(const ImageSingleton&) {};
// 	static ImageSingleton m_instance;
// 	ImageSingleton();
// 	~ImageSingleton();
// };