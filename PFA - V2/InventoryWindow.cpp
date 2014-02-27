#include "InventoryWindow.h"
#include "GameScreen.h"
#include "ImageSingleton.h"
#include "Singleton.h"
#include <iostream>
#include <sstream>
#include "Drops.h"
#include "MapEnvironment.h"


InventoryWindow::InventoryWindow()
{
	createWindow();
	createToolbar();
	this->_gameScreen = NULL;
	this->_selectedRessource = NULL;
	this->_crafting = NULL;
	_isInInventoryScroll = false;
	_isInSpinButton = false;
}

void InventoryWindow::createToolbar()
{
	this->_spinButton = sfg::SpinButton::Create(0.f, 18.f, 1.f);
	this->_spinButton->SetValue(0);
	this->_spinButton->SetRange(0, 0);
	this->_spinButton->SetId("_spinButton");
	this->_spinButton->GetSignal(sfg::Widget::OnMouseEnter).Connect(std::bind(&InventoryWindow::mouseEnter, this, this->_spinButton->GetId()));
	this->_spinButton->GetSignal(sfg::Widget::OnMouseLeave).Connect(std::bind(&InventoryWindow::mouseLeave, this, this->_spinButton->GetId()));

	this->_toolbar = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL);
	this->_toolbar->SetRequisition(sf::Vector2f(100.f, 50.f));
	auto useButton = sfg::Button::Create("Use");
	useButton->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&InventoryWindow::useClick, this));
	auto dropButton = sfg::Button::Create("Drop");
	dropButton->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&InventoryWindow::dropClick, this));
	auto craftButton = sfg::Button::Create("Craft");
	craftButton->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&InventoryWindow::craftClick, this));
	auto stuffButton = sfg::Button::Create("Stuff");
	/*TODO signaux*/
	this->_toolbar->Pack(useButton);
	this->_toolbar->Pack(this->_spinButton);
	this->_toolbar->Pack(dropButton);
	this->_toolbar->Pack(craftButton);
	this->_toolbar->Pack(stuffButton);
	this->_mainBox->PackEnd(this->_toolbar);
}

void InventoryWindow::createWindow()
{
	this->_inventoryWindow = sfg::Window::Create(sfg::Window::Style::TITLEBAR | sfg::Window::Style::BACKGROUND);
	this->_inventoryWindow->Show(false);
	this->_inventoryWindow->SetTitle("Inventory");
	this->_inventoryWindow->SetPosition(sf::Vector2f(150.f, 100.f));
	this->_emptyLabel = sfg::Label::Create("Pas de joueur(s) sélectionné(s).");
	this->_mainBox = sfg::Box::Create(sfg::Box::Orientation::VERTICAL);
	this->_inventoryBox = sfg::Box::Create(sfg::Box::Orientation::VERTICAL);

	this->_scroll = sfg::ScrolledWindow::Create();

	this->_scroll->SetScrollbarPolicy(sfg::ScrolledWindow::VERTICAL_ALWAYS | sfg::ScrolledWindow::HORIZONTAL_NEVER);
	this->_scroll->AddWithViewport(this->_inventoryBox);
	this->_scroll->SetId("_inventoryScroll");
	this->_scroll->GetSignal(sfg::Widget::OnMouseEnter).Connect(std::bind(&InventoryWindow::mouseEnter, this, this->_scroll->GetId()));
	this->_scroll->GetSignal(sfg::Widget::OnMouseLeave).Connect(std::bind(&InventoryWindow::mouseLeave, this, this->_scroll->GetId()));

	// Always remember to set the minimum size of a ScrolledWindow.
	this->_scroll->SetRequisition(sf::Vector2f(280.f, 550.f));
	this->_mainBox->Pack(this->_scroll, true, true);
	this->_inventoryWindow->Add(this->_mainBox);
	Singleton::getInstance()._desktop.Add(this->_inventoryWindow);
}

void InventoryWindow::dropClick()
{
	Drops *drop = new Drops;
	if (this->_selectedRessource != NULL)
	{
		if (this->_selectedRessource->_button->IsActive() == true)
		{
			//TODO le supprimer de l'inventaire, et mettre le coffre a coté de nous
			drop->addDrop(this->_selectedRessource->getCompartment()->getElements(this->_spinButton->GetValue()));
			this->_selectedRessource->getPlayer()->getMap()->getEntitiesMap()[(int)this->_selectedRessource->getPlayer()->getPosition().y][(int)this->_selectedRessource->getPlayer()->getPosition().x]._component = drop;
			this->_selectedRessource->_button->SetActive(false);
			this->_spinButton->SetValue(0);
			this->_spinButton->SetRange(0, 0);
		}
	}
}

void InventoryWindow::craftClick()
{
	if (this->_selectedRessource != NULL)
	{
		this->_crafting->addInTable(this->_selectedRessource, this->_spinButton->GetValue());
		this->_selectedRessource->_button->SetActive(false);
		this->_selectedRessource = NULL;
		this->_spinButton->SetValue(0);
		this->_spinButton->SetRange(0, 0);
	}
}

void InventoryWindow::mouseEnter(std::string const&id)
{
	if (id == "_inventoryScroll")
		this->_isInInventoryScroll = true;
	else if (id == "_spinButton")
		this->_isInSpinButton = true;
}

void InventoryWindow::mouseLeave(std::string const&id)
{
	if (id == "_inventoryScroll")
		this->_isInInventoryScroll = false;
	else if (id == "_spinButton")
		this->_isInSpinButton = false;
}


void InventoryWindow::createZones(std::vector<Player *>& players)
{
	this->_players = players;
	for (Player *u : players)
	{
		createCompartment(u);
	}
		
}

void InventoryWindow::setCraftingClass(Crafting *craft)
{
	this->_crafting = craft;
}


void  InventoryWindow::addToInventory(Player *player, Compartment *com, int pos)
{
	std::cout << "Jajoute dans l'inventaire  " << std::endl;
	int compt = 0;
	//savoir sa position
	std::cout << "Nbr players :" << this->_players.size() << std::endl;
	for (Player *u : this->_players)
	{
		std::cout << "Player : " << u->getName() << std::endl;
		std::cout << "Jajoute dans l'inventaire  " << std::endl;
		if (u == player)
		{
			std::cout << "Je suis le player ! :)" << std::endl;
			CustomToggleButton *u = this->_tableButtons[8 * compt + pos];
			u->setCompartment(com);
			break;
		}
		++compt;
	}
}

void InventoryWindow::fillImage(Player *player, int index, sfg::ToggleButton::Ptr but)
{
	Compartment *compartment = player->getCompartment(index);
	if (compartment != NULL)
	{
		but->SetImage(sfg::Image::Create(compartment->getImage()));
	}
}

void	InventoryWindow::showBox(std::vector<Player *>&players)
{
	int compt = 0;
	while (compt < players.size())
	{
		if (this->_tableBox[compt]->IsLocallyVisible() == true && players[compt]->getSelected() == false)
		{
			this->_inventoryBox->Remove(this->_tableBox[compt]);
			this->_tableBox[compt]->Show(false);
		}
		else if (this->_tableBox[compt]->IsLocallyVisible() == false && players[compt]->getSelected() == true)
		{
			this->_inventoryBox->Pack(this->_tableBox[compt]);
			this->_tableBox[compt]->Show(true);
		}
		++compt;
	}
	this->_scroll->Refresh();
}

void InventoryWindow::useClick()
{
	if (this->_selectedRessource != NULL)
	{
		std::list<IEntity *> list = this->_selectedRessource->getEntities();
		int compt = this->_spinButton->GetValue();
		while (compt > 0)
		{
			list.front()->doAction(this->_selectedRessource->getPlayer());
			compt--;
		}
		compt = this->_spinButton->GetValue();
		this->_selectedRessource->_button->SetActive(false);
		this->_spinButton->SetValue(0);
		this->_spinButton->SetRange(0, 0);
		if (compt == this->_selectedRessource->getCompartment()->getSize())
		{
			this->_selectedRessource->getCompartment()->delAllElement();
			this->_selectedRessource->_button->ClearImage();
			this->_selectedRessource = NULL;
		}
		else
		{
			while (compt > 0)
			{
				this->_selectedRessource->getCompartment()->delElement();
				compt--;
			}
		}
	}
}

void InventoryWindow::mouseLeftPress(CustomToggleButton *but)
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
		this->_spinButton->SetValue(0);
		this->_spinButton->SetRange(0, 0);

	}
	else
	{
		this->_selectedRessource = but;
		this->_spinButton->SetRange(0, but->getCompartment()->getSize());
		this->_spinButton->SetValue(but->getCompartment()->getSize());
	}
	for (CustomToggleButton *u : this->_tableButtons)
	{
		if (u->_button->IsActive() == true && (but != u))
		{
			u->_button->SetActive(false);
			return;
		}
	}
}

void InventoryWindow::createCompartment(Player *player)
{
	int compt = 0;
	auto box = sfg::Box::Create(sfg::Box::Orientation::VERTICAL);

	auto table = sfg::Table::Create();
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			CustomToggleButton *but = new CustomToggleButton(player, player->getCompartment(compt));
			but->_button->SetRequisition(sf::Vector2f(180.f, 166.f));
			but->_button->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&InventoryWindow::mouseLeftPress, this, but));
			this->_tableButtons.push_back(but);
			table->Attach(but->_button, sf::Rect<sf::Uint32>(j, i, 1, 1), sfg::Table::FILL | sfg::Table::EXPAND, sfg::Table::FILL, sf::Vector2f(10.f, 10.f));
			++compt;
		}
	}
	box->Pack(sfg::Label::Create(player->getName()));
	box->Pack(table);
	this->_tables.push_back(table);
	this->_tableBox.push_back(box);
	this->_inventoryBox->PackEnd(box);
}
void InventoryWindow::init()
{
	//A mettre dans le singleton 
	this->_img.loadFromFile("./Media/images/carre.png");
}

void InventoryWindow::close()
{
	std::cout << "JE PASSE DANS CLOSE " << std::endl;
	//this->_inventoryWindow->Show(false);
}

void InventoryWindow::checkScrollEvent()
{
	if (this->_isInInventoryScroll == true && Singleton::getInstance().deltaMouseWeel != 0)
	{
		if (Singleton::getInstance().deltaMouseWeel > 0)
			this->_scroll->GetVerticalAdjustment()->SetValue(this->_scroll->GetVerticalAdjustment()->GetValue() - 60);
		else
			this->_scroll->GetVerticalAdjustment()->SetValue(this->_scroll->GetVerticalAdjustment()->GetValue() + 60);
	}
	else if (this->_isInSpinButton == true && Singleton::getInstance().deltaMouseWeel != 0)
	{
		int value = this->_spinButton->GetValue();
		this->_spinButton->SetValue(value + Singleton::getInstance().deltaMouseWeel);
	}
	Singleton::getInstance().deltaMouseWeel = 0;
}

void InventoryWindow::update()
{
	checkScrollEvent();
	Singleton::getInstance()._desktop.Update(0.1f);
}

void InventoryWindow::draw()
{
	Singleton::getInstance()._sfgui.Display(*Singleton::getInstance()._window);
}

InventoryWindow::~InventoryWindow()
{
}
