#include "FontManager.h"

FontManager FontManager::_instance = FontManager();

FontManager::FontManager()
{
	_fonts[SANSATION] = new sf::Font();
	_fonts[SANSATION]->loadFromFile(MEDIA + std::string("Sansation.ttf"));
}

FontManager &FontManager::getInstance()
{
	return _instance;
}

FontManager::~FontManager()
{
}

sf::Font *FontManager::getFont(Fonts font)
{
	return _fonts[font];
}