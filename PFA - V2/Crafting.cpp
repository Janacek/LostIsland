#include "Crafting.h"


Crafting::Crafting()
{
	this->_isNearTable = false;
	createWindow();
	createTables();
}

void Crafting::createWindow()
{
	this->_craftingWindow = sfg::Window::Create(sfg::Window::Style::TITLEBAR | sfg::Window::Style::BACKGROUND);
	this->_craftingWindow->SetTitle("Crafting");
	this->_craftingWindow->SetPosition(sf::Vector2f(1100, 100));
	this->_craftingWindow->Show(false);
	this->_mainBox = sfg::Box::Create(sfg::Box::Orientation::VERTICAL);
	this->_craftingWindow->Add(this->_mainBox);
	Singleton::getInstance()._desktop.Add(this->_craftingWindow);
}

void Crafting::createTables()
{
	int compt = 0; 
	auto craftButton = sfg::Button::Create("Craft");
	craftButton->SetRequisition(sf::Vector2f(100.f, 50.f));
	this->_boxButtons = sfg::Box::Create(sfg::Box::Orientation::VERTICAL);
	this->_smallTable = sfg::Table::Create();

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			CustomToggleButton *but = new CustomToggleButton(NULL, NULL);
			but->_button->SetRequisition(sf::Vector2f(180.f, 166.f));
			but->_button->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&Crafting::mouseLeftPress, this));
			this->_smallTable->Attach(but->_button, sf::Rect<sf::Uint32>(j, i, 1, 1), sfg::Table::FILL | sfg::Table::EXPAND, sfg::Table::FILL, sf::Vector2f(10.f, 10.f));
			++compt;
		}
	}
	this->_boxButtons->Pack(this->_smallTable);
	this->_mainBox->Pack(this->_boxButtons);
	this->_mainBox->PackEnd(craftButton);
	compt = 0;
	this->_largeTable = sfg::Table::Create();

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			CustomToggleButton *but = new CustomToggleButton(NULL, NULL);
			but->_button->SetRequisition(sf::Vector2f(180.f, 166.f));
			but->_button->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&Crafting::mouseLeftPress, this));
			this->_largeTable->Attach(but->_button, sf::Rect<sf::Uint32>(j, i, 1, 1), sfg::Table::FILL | sfg::Table::EXPAND, sfg::Table::FILL, sf::Vector2f(10.f, 10.f));
			++compt;
		}
	}
}

void Crafting::chooseDistance(Crafting::Distance dist)
{
	if (dist == Distance::NEARTABLE)
	{
		this->_boxButtons->Remove(this->_smallTable);
		this->_smallTable->Show(false);
		this->_boxButtons->Pack(this->_largeTable);
		this->_largeTable->Show(true);
	}
	else if (dist == Distance::FARTABLE)
	{
		this->_boxButtons->Remove(this->_largeTable);
		this->_largeTable->Show(false);
		this->_boxButtons->Pack(this->_smallTable);
		this->_smallTable->Show(true);
	}
}

bool Crafting::isNearTable() const
{
	return this->_isNearTable;
}

void  Crafting::Show(bool show)
{
	this->_craftingWindow->Show(show);
}

void	Crafting::update()
{

}

void Crafting::draw()
{

}

void	Crafting::mouseLeftPress()
{

}

Crafting::~Crafting()
{
}
