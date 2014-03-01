#pragma once

#include						<SFML/Window.hpp>
#include						<SFML/Graphics.hpp>

#include <map>
#include <string>
#include <memory>
#include <stdexcept>
#include <cassert>

#include "AEntity.h"

class ImageManager
{
public:
	static ImageManager& getInstance();

	void start();
	void load(Type id,
		const std::string& filename);
	sf::Texture *get(Type id);
private:
	ImageManager(const ImageManager&) {};
	static ImageManager m_instance;
	ImageManager();
	~ImageManager();
	std::map<Type,	sf::Texture *> _mapTexture;
};