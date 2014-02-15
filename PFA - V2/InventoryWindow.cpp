#include "InventoryWindow.h"
#include "GameScreen.h"
#include <iostream>
#include <sstream>


InventoryWindow::InventoryWindow()
{
	createWindow();
	createToolbar();
	this->_gameScreen = NULL;
	this->_selectedRessource = NULL;
}

void InventoryWindow::createToolbar()
{
	this->_toolbar = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL);
	auto useButton = sfg::Button::Create("Use");
	useButton->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&InventoryWindow::useClick, this));
	auto dropButton = sfg::Button::Create("Drop");
	auto craftButton = sfg::Button::Create("Craft");
	auto stuffButton = sfg::Button::Create("Stuff");
	/*TODO signaux*/
	this->_toolbar->Pack(useButton);
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
	this->_inventoryWindow->SetPosition(sf::Vector2f(150, 100));
	this->_emptyLabel = sfg::Label::Create("Pas de joueur(s) sélectionné(s)."); 
	this->_mainBox = sfg::Box::Create(sfg::Box::Orientation::VERTICAL);
	this->_inventoryBox = sfg::Box::Create(sfg::Box::Orientation::VERTICAL);
	this->_scroll  = sfg::ScrolledWindow::Create();

	this->_scroll->SetScrollbarPolicy(sfg::ScrolledWindow::VERTICAL_AUTOMATIC | sfg::ScrolledWindow::HORIZONTAL_NEVER);
	this->_scroll->AddWithViewport(this->_inventoryBox);

	// Always remember to set the minimum size of a ScrolledWindow.
	this->_scroll->SetRequisition(sf::Vector2f(280.f, 550.f));
	this->_mainBox->Pack(this->_scroll, true, true);
	this->_inventoryWindow->Add(this->_mainBox);
	Singleton::getInstance()._desktop.Add(this->_inventoryWindow);
}

void InventoryWindow::createZones(std::vector<Player *>& players)
{
	for (Player *u : players)
		createCompartment(u);
}

void  InventoryWindow::addToInventory(Player *player, IEntity *entity)
{
	for (Player * u : this->_players)
	{
		//si c'est ce player
		if (u == player)
		{
			u->addEntityInInventory(entity);
			int pos = u->posInventory(entity);
			std::cout << "POS : " << pos << std::endl;
			this->_tableImages[pos]->SetImage((*ImageSingleton::getInstance().get(entity->getType())).copyToImage());
		}
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
	for (CustomToggleButton *u : this->_tableButtons)
	{
		if (u->_button->IsActive() == true)
		{
			std::list<IEntity *> list = u->getEntities();
			for (IEntity *i : list)
			{
				i->doAction(u->getPlayer());
			}
			u->getCompartment()->delAllElement();
			u->_button->SetActive(false);
			u->_button->ClearImage();
			break;
		}
	}
}

void InventoryWindow::mouseLeftPress(CustomToggleButton *but)
{
	if (but->_button->IsActive() == true && but->isEmpty() == true)
	{
		but->_button->SetActive(false);
		return;
	}
	else
		this->_selectedRessource = but;
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
	this->_img.loadFromFile("carre.png");
}

void InventoryWindow::close()
{
	this->_inventoryWindow->Show(false);
}

void InventoryWindow::update()
{
	Singleton::getInstance()._desktop.Update(0.1f);
}

void InventoryWindow::draw()
{
	Singleton::getInstance()._sfgui.Display(*Singleton::getInstance()._window);
}

InventoryWindow::~InventoryWindow()
{
}
