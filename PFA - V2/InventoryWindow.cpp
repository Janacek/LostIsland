#include "InventoryWindow.h"
#include "GameScreen.h"
#include <iostream>
#include <sstream>


InventoryWindow::InventoryWindow()
{
	createWindow();
	createNumberWindow();
	this->_gameScreen = NULL;
	this->_dropNbr = 0;
	this->_tableTest = sfg::Table::Create();
	auto but = sfg::Button::Create("Prout");
	this->_tableTest->Add(but);
}

void InventoryWindow::createNumberWindow()
{
	this->_numberWindow = sfg::Window::Create();
	this->_numberWindow->Show(false);
	this->_numberWindow->SetTitle("Choose number");
	auto box = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL);
	auto button = sfg::Button::Create();
	button->SetLabel("Valider");
	button->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&InventoryWindow::valideNumber, this));
	this->_label = sfg::Label::Create();
	this->_entry = sfg::Entry::Create();
	this->_entry->GetSignal(sfg::Widget::OnText).Connect(std::bind(&InventoryWindow::onTextChange, this));
	this->_entry->SetRequisition(sf::Vector2f(80.f, 0.f));
	box->Pack(this->_entry);
	box->Pack(button);
	box->Pack(this->_label);
	box->SetSpacing(5.f);
	this->_numberWindow->Add(box);
	this->_desktop.Add(this->_numberWindow);
}

void InventoryWindow::createWindow()
{
	this->_inventoryWindow = sfg::Window::Create(sfg::Window::Style::TITLEBAR | sfg::Window::Style::BACKGROUND);
	this->_inventoryWindow->Show(false);
	this->_inventoryWindow->SetRequisition(sf::Vector2f(500, 300.0f));
	this->_inventoryWindow->SetTitle("Inventory");
	this->_inventoryWindow->GetSignal(sfg::Widget::OnMouseLeave).Connect(std::bind(&GestionClick::drop, &this->_gestionClick));
	this->_inventoryWindow->GetSignal(sfg::Widget::OnMouseEnter).Connect(std::bind(&GestionClick::cantDrop, &this->_gestionClick));
	//je ne sais pas comment faire pour qu'il se mette juste en bas de la page..
	/*this->_closeButton = sfg::Button::Create("Close");
	this->_closeButton->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&InventoryWindow::close, this));
	this->_inventoryWindow->Add(this->_closeButton);*/

	this->_desktop.Add(this->_inventoryWindow);
}

void InventoryWindow::createTabs(std::vector<Player *>&players)
{
	this->_players = players;
	this->_notebookfirst = sfg::Notebook::Create();
	this->_inventoryWindow->Add(this->_notebookfirst);
	//On crée un onglet pour chaque players
	for (Player *u : this->_players)
		createCompartment(u);
}

void InventoryWindow::chooseNumber(GameScreen *gameS)
{
	if (this->_numberWindow->IsLocallyVisible())
		return;
	this->_gameScreen = gameS;
	std::cout << "choose Nummmmber " << std::endl;
	this->_entry->SetText("");
	this->_numberWindow->SetPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(*Singleton::getInstance()._window)));
	this->_numberWindow->Show();
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

void InventoryWindow::valideNumber()
{
	std::istringstream  ss(this->_entry->GetText());

	int nbr;

	//TODO : faire une vérif
	ss >> this->_dropNbr;
	//TODO : vider la case du bon nbr de ressources
	s_action tmp = this->dropRessource();
	if (tmp._compartment == NULL)
		std::cout << "NULLLLLLLLLLLLLLLLLLLL dans la verif" << std::endl;
	system("pause");
	tmp._img->SetImage(this->_img);
	tmp._compartment->delElement();
	this->_gestionClick.clearLastCompartment();
	this->_numberWindow->Show(false);
	this->_gameScreen->validDrop(this->_dropNbr);
}

void InventoryWindow::onTextChange()
{
	//Il faudra vérifier que c'est bien des nombres, et pas un nombre au dessus du nombre de ressources
}

Compartment  *InventoryWindow::dropRessource()
{
	s_action tmp = this->_gestionClick.canDrop();
	if (tmp._compartment != NULL)
	{
		//TODO ne pas faire ça si y'a plusieurs ressources
		tmp._img->SetImage(this->_img);
		//gerer affichage
	}
	return tmp._compartment;
}

void InventoryWindow::mouseLeftPress(int index)
{
	std::cout << "press : index : " << index << std::endl;
}

void InventoryWindow::mouseLeftRelease(int index)
{
	std::cout << "release : index " << index << std::endl;
}

const sf::Image&InventoryWindow::fillImage(Player *player, int index)
{
	Compartment *compartment = player->getCompartment(index);
	if (compartment == NULL)
		return this->_img;
	else
		return compartment->getImage();
}

void InventoryWindow::createCompartment(Player *player)
{
	std::cout << "Yeah " << std::endl;
	int compt = 0;
	auto table = sfg::Table::Create();
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			auto tmp = sfg::Image::Create();
			this->_tableImages.push_back(tmp);
			tmp->SetImage(fillImage(player, compt));
			tmp->GetSignal(sfg::Widget::OnMouseLeftPress).Connect(std::bind(&GestionClick::leftPress, &this->_gestionClick, compt, player, tmp));
			//	tmp->GetSignal(sfg::Widget::OnMouseEnter).Connect(std::bind(&GestionClick::dump, &this->_gestionClick, compt, player));
			//	tmp->GetSignal(sfg::Widget::OnMouseLeftRelease).Connect(std::bind(&GestionClick::leftRelease, &this->_gestionClick, compt, player, tmp));
			table->Attach(tmp, sf::Rect<sf::Uint32>(j, i, 1, 1), sfg::Table::FILL | sfg::Table::EXPAND, sfg::Table::FILL, sf::Vector2f(10.f, 10.f));
			++compt;
		}
	}
	this->_tables.push_back(table);
	//this->_notebookfirst->AppendPage(table, sfg::Label::Create(player->getName()));
}
void InventoryWindow::init()
{
	//A mettre dans le singleton 
	this->_img.loadFromFile("carre.png");
	this->_test.loadFromFile("water.png");
}

void InventoryWindow::close()
{
	this->_inventoryWindow->Show(false);
}

void InventoryWindow::update()
{
	_desktop.Update(0.1f);
}

void InventoryWindow::draw()
{
	Singleton::getInstance()._sfgui.Display(*Singleton::getInstance()._window);
}

InventoryWindow::~InventoryWindow()
{
}
