#pragma once

#include <map>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "SystemDefines.h"

enum Fonts
{
	SANSATION,
};

class FontManager
{
public:
	static FontManager &getInstance();
	sf::Font *getFont(Fonts);

private:
	FontManager(const FontManager&) {};
	static FontManager _instance;
	FontManager();
	~FontManager();

	std::map<Fonts, sf::Font *>		_fonts;
};