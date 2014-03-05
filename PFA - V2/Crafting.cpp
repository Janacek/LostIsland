#include "Crafting.h"
#include "ImageManager.h"
#include "Water.h"
#include "Rock.h"
#include "Wood.h"
#include "InventoryWindow.h"

Crafting::Crafting()
{
	if (this->_databaseManager.openDatabase("Media/database/craft.db") == false)
		std::cout << "Error open database" << std::endl;
	this->_objectCraft = NULL;
	createWindow();
	createChooseWindow();
	createTables();
}

void Crafting::createChooseWindow()
{
	this->_choosePlayerWindow = sfg::Window::Create(sfg::Window::Style::TITLEBAR | sfg::Window::Style::BACKGROUND);
	this->_choosePlayerWindow->SetTitle("Choose where the craft will be send");
	this->_choosePlayerWindow->SetPosition(sf::Vector2f(1300, 400));
	this->_choosePlayerWindow->SetRequisition(sf::Vector2f(300.f, 200.f));
	this->_choosePlayerWindow->Show(false);
	Singleton::getInstance()._desktop.Add(this->_choosePlayerWindow);
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
	auto img = sfg::Image::Create();
	img->SetRequisition(sf::Vector2f(180.f, 166.f));
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
				this->_imgResult = sfg::Image::Create();
				this->_imgResult->SetRequisition(sf::Vector2f(180.f, 166.f));
				this->_largeTable->Attach(this->_imgResult, sf::Rect<sf::Uint32>(1, 1, 1, 1), sfg::Table::FILL | sfg::Table::EXPAND, sfg::Table::FILL, sf::Vector2f(10.f, 10.f));
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

void Crafting::setInventoryClass(InventoryWindow *i)
{
	this->_inventoryWindow = i;
}

void Crafting::createChooseWindowContent()
{
	auto box = sfg::Box::Create(sfg::Box::Orientation::VERTICAL);
	for (Player *u : this->_inventoryWindow->getPlayers())
	{
		auto but = sfg::Button::Create(u->getName());
		but->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&Crafting::validCraft, this, u));
		box->Pack(but);
	}
	this->_choosePlayerWindow->Add(box);
}

void	Crafting::updateContent()
{
	this->_content.clear();
	for (auto u : this->_tableButton)
	{
		if (u->getCompartment() != NULL)
		{
			this->_content.push_back(u->getEntities().front());
		}
	}
}

void Crafting::deleteEntities()
{
	int compt = 0;
	for (AEntity *entity : this->_content)
	{
		for (Player *u : this->_inventoryWindow->getPlayers())
		{
			if (u->delEntityInInventory(entity) == true)
			{
				break;
			}
		}
	}
	//Clear graphique
	for (CustomToggleButton *u : this->_tableButton)
		u->empty();
	this->_imgResult->Show(false);
}

void	Crafting::validCraft(Player *p)
{
	deleteEntities();
	this->_inventoryWindow->updateView();
	p->addEntityInInventory(this->_objectCraft);
	this->_objectCraft = NULL;
	this->_choosePlayerWindow->Show(false);
}

void Crafting::craft()
{
	if (this->_choosePlayerWindow->IsLocallyVisible() == false) //si on a pas deja cliqué une fois sur craft
	{
		if (this->_objectCraft != NULL)
		{
			std::cout << "Je suis show ! " << std::endl;
			this->_choosePlayerWindow->Show(true);
			Singleton::getInstance()._desktop.BringToFront(this->_choosePlayerWindow);
		}
	}
	else
	{
		Singleton::getInstance()._desktop.BringToFront(this->_choosePlayerWindow);
	}
}

void Crafting::remove()
{
	if (this->_selectedRessource != NULL)
	{
		delete this->_objectCraft;
		this->_objectCraft = NULL;
		this->_selectedRessource->_button->SetActive(false);
		this->_selectedRessource->setCompartment(NULL);
		this->updateContent();
		this->updateImgResult();
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
	this->updateContent();
	this->updateImgResult();
}

void   Crafting::updateImgResult()
{
	std::string result = this->_databaseManager.askTable(this->_content);
	std::cout << "RESULT : " << result << std::endl;
	if (this->_objectCraft != NULL)
	{
		delete this->_objectCraft;
		this->_objectCraft = NULL;
	}
	if (result != "")
	{
		this->_objectCraft = this->_entityFactory.makeEntity(result);
		this->_imgResult->SetImage((*ImageManager::getInstance().get(this->_objectCraft->getType())).copyToImage());
		this->_imgResult->Show(true);
	}
	else
	{
		this->_imgResult->Show(false);
	}
}

void  Crafting::Show(bool show)
{
	this->_craftingWindow->Show(show);
	this->_choosePlayerWindow->Show(false);
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
