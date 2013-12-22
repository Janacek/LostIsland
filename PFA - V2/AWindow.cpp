#include "AWindow.h"
#include "Singleton.h"


AWindow::AWindow(std::string const &title, float sizeX, float sizeY, float posX, float posY)
{
	//Fenetre principale
	this->_window.setSize(sf::Vector2f(sizeX, sizeY));
	this->_window.setPosition(posX, posY);
	this->_window.setFillColor(sf::Color::White);

	//Bannière : taille fixe, donc en fonction de la fenetre principale
	this->_banner.setSize(sf::Vector2f(sizeX, Singleton::getInstance()._window->getSize().y * 4 / 100));
	this->_banner.setPosition(posX, posY - Singleton::getInstance()._window->getSize().y * 4 / 100);
	this->_banner.setFillColor(sf::Color::Cyan);

	//Texte dans la bannière
	this->_font = new sf::Font;
	if (this->_font->loadFromFile("./Media/Sansation.ttf") == false)
		std::cout << "ERROR lors du load de la font" << std::endl;
	this->_title.setFont(*this->_font);
	this->_title.setCharacterSize(19);
	this->_title.setColor(sf::Color::Magenta);
	this->_title.setString(title);
	this->_title.setPosition(posX + this->_banner.getSize().x / 2 - (title.size() / 2) - this->_banner.getSize().x * 8 / 100, this->_banner.getPosition().y);

	//Bouton de fermeture
	this->_closeButton.setSize(sf::Vector2f(sizeX * 8 / 100, this->_banner.getSize().y));
	this->_closeButton.setPosition(posX + this->_banner.getSize().x * 92 / 100, this->_banner.getPosition().y);
	this->_closeButton.setFillColor(sf::Color::Red);
	this->_close = false;
}

void AWindow::checkClose()
{
	float leftCompartment = this->_closeButton.getGlobalBounds().left;
	float rightCompartment = this->_closeButton.getGlobalBounds().width + leftCompartment;
	float topCompartment = this->_closeButton.getGlobalBounds().top;
	float bottomCompartment = topCompartment + this->_closeButton.getGlobalBounds().height;
	sf::Vector2i posLeftClickPressed = Singleton::getInstance().posLeftClickPressed;
	if (posLeftClickPressed.x != -1  && leftCompartment <= posLeftClickPressed.x && rightCompartment >= posLeftClickPressed.x && topCompartment <= posLeftClickPressed.y && bottomCompartment >= posLeftClickPressed.y)
	{
		Singleton::getInstance().posLeftClickPressed.x = -1;
		this->_close = true;
	}
}

bool AWindow::clickInWindow()
{
	float leftCompartment = this->_window.getGlobalBounds().left;
	float rightCompartment = this->_window.getGlobalBounds().width + leftCompartment;
	float topCompartment = this->_window.getGlobalBounds().top;
	float bottomCompartment = topCompartment + this->_window.getGlobalBounds().height;
	sf::Vector2i posLeftClickPressed = Singleton::getInstance().posLeftClickPressed;
	if (posLeftClickPressed.x != -1  && leftCompartment <= posLeftClickPressed.x && rightCompartment >= posLeftClickPressed.x && topCompartment <= posLeftClickPressed.y && bottomCompartment >= posLeftClickPressed.y)
	{
		//clickInCompartment();
		Singleton::getInstance().posLeftClickPressed.x = -1;
		std::cout << "Je clique dans la fenetre" << std::endl;
		return true;
	}
	return true;
}

void AWindow::draw()
{
	Singleton::getInstance()._window->draw(this->_window);
	Singleton::getInstance()._window->draw(this->_banner);
	Singleton::getInstance()._window->draw(this->_title);
	Singleton::getInstance()._window->draw(this->_closeButton);
	for (Compartment *u : this->_compartments)
		u->draw();
}

AWindow::~AWindow(void)
{
}
