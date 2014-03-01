#include "Crafting.h"
#include "ImageManager.h"
#include "Water.h"
#include "Rock.h"
#include "Wood.h"

Crafting::Crafting()
{
	this->_isNearTable = false;
	if (this->_databaseManager.openDatabase("Media/database/craft.db") == false)
		std::cout << "Error open database" << std::endl;
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
	auto craftButton = sfg::Button::Create("Craft");
	auto removeButton = sfg::Button::Create("Supprimer de la table");
	craftButton->SetRequisition(sf::Vector2f(100.f, 50.f));
	craftButton->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&Crafting::craft, this));
	removeButton->SetRequisition(sf::Vector2f(100.f, 50.f));
	removeButton->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&Crafting::remove, this));
	this->_boxButtons = sfg::Box::Create(sfg::Box::Orientation::VERTICAL);
	this->_smallTable = sfg::Table::Create();

	for (int i = 0; i < 3; i += 2)
	{
		for (int j = 0; j < 3; j += 2)
		{
			CustomToggleButton *but = new CustomToggleButton(NULL, NULL);
			but->_button->SetRequisition(sf::Vector2f(180.f, 166.f));
			but->_button->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&Crafting::mouseLeftPress, this, but));
			this->_smallTable->Attach(but->_button, sf::Rect<sf::Uint32>(j, i, 1, 1), sfg::Table::FILL | sfg::Table::EXPAND, sfg::Table::FILL, sf::Vector2f(10.f, 10.f));
		}
	}
	auto img = sfg::Image::Create();
	img->SetRequisition(sf::Vector2f(180.f, 166.f));
	this->_smallTable->Attach(img, sf::Rect<sf::Uint32>(1, 1, 1, 1), sfg::Table::FILL | sfg::Table::EXPAND, sfg::Table::FILL, sf::Vector2f(10.f, 10.f));
	/*this->_boxButtons->Pack(this->_smallTable);*/
	this->_mainBox->Pack(this->_boxButtons);
	this->_mainBox->PackEnd(craftButton);
	this->_mainBox->PackEnd(removeButton);
	this->_largeTable = sfg::Table::Create();

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (i == 1 && j == 1)
			{
				auto img2 = sfg::Image::Create();
				img2->SetRequisition(sf::Vector2f(180.f, 166.f));
				this->_largeTable->Attach(img2, sf::Rect<sf::Uint32>(1, 1, 1, 1), sfg::Table::FILL | sfg::Table::EXPAND, sfg::Table::FILL, sf::Vector2f(10.f, 10.f));
			}
			else
			{
				CustomToggleButton *but = new CustomToggleButton(NULL, NULL);
				this->_tableButton.push_back(but);
				but->_button->SetRequisition(sf::Vector2f(180.f, 166.f));
				but->_button->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&Crafting::mouseLeftPress, this, but));
				this->_largeTable->Attach(but->_button, sf::Rect<sf::Uint32>(j, i, 1, 1), sfg::Table::FILL | sfg::Table::EXPAND, sfg::Table::FILL, sf::Vector2f(10.f, 10.f));
			}
		}
		this->_boxButtons->Pack(this->_largeTable);
	}
}

void Crafting::craft()
{
	std::vector<AEntity *> tmp;
	//Wood = wooden_plank tmp
	tmp.push_back(new Wood);
	tmp.push_back(new Wood);
	//this->_databaseManager.dumpTable();
	this->_databaseManager.askTable(SWORD, tmp);
}

void Crafting::remove()
{
	if (this->_selectedRessource != NULL)
	{
		this->_selectedRessource->_button->SetActive(false);
		this->_selectedRessource->setCompartment(NULL);
	}
}

void Crafting::addInTable(CustomToggleButton *button, int nbr)
{
	for (auto u : this->_tableButton)
	{
		if (u->getCompartment() == NULL)
		{
			u->setCompartment(button->getCompartment());
			break;
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

void	Crafting::mouseLeftPress(CustomToggleButton *but)
{
	if (but->_button->IsActive() == true && but->isEmpty() == true)
	{
		//	this->_spinButton->SetValue(0);
		but->_button->SetActive(false);
		return;
	}
	else if (but->_button->IsActive() == false)
	{
		this->_selectedRessource = NULL;
	}
	else
	{
		this->_selectedRessource = but;
	}
	for (CustomToggleButton *u : this->_tableButton)
	{
		if (u->_button->IsActive() == true && (but != u))
		{
			u->_button->SetActive(false);
			return;
		}
	}
}

Crafting::~Crafting()
{
}
