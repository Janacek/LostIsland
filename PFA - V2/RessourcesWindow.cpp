#include "RessourcesWindow.h"
#include "Singleton.h"
#include "ImageSingleton.h"
#include "GameScreen.h"
#include <iostream>


RessourcesWindow::RessourcesWindow(GameScreen *game)
{
	createWindow(game);
	this->_img.loadFromFile("carre.png");
	createCompartment();
}

void RessourcesWindow::createWindow(GameScreen *game)
{
	this->_ressourcesWindow = sfg::Window::Create(sfg::Window::Style::TITLEBAR | sfg::Window::Style::BACKGROUND);
	this->_ressourcesWindow->SetTitle("Choix des ressources");
	this->_ressourcesWindow->SetRequisition(sf::Vector2f(500, 300.0f));
	this->_ressourcesWindow->Show(false);
	this->_getButton = sfg::Button::Create("Récupérer la ressource");
	this->_getButton->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&RessourcesWindow::clickOnGetButton, this, game));
	Singleton::getInstance()._desktop.Add(this->_ressourcesWindow);
}

void RessourcesWindow::createCompartment()
{
	int compt = 0;
	char id = 'a';
	std::string my_id;

	my_id = id;
	auto box = sfg::Box::Create(sfg::Box::Orientation::VERTICAL);
	box->SetRequisition(sf::Vector2f(500, 300.0f));
	auto table = sfg::Table::Create();
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			auto but = sfg::ToggleButton::Create();

			auto tmp = sfg::Image::Create();
			but->SetImage(tmp);
			this->_tableImages.push_back(tmp);
			this->_tableButtons.push_back(but);
			but->SetId(my_id);
			but->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&RessourcesWindow::selectRessource, this, compt));
			table->Attach(but, sf::Rect<sf::Uint32>(j, i, 1, 1), sfg::Table::FILL | sfg::Table::EXPAND, sfg::Table::FILL, sf::Vector2f(10.f, 10.f));
			++compt;
			my_id.clear();
			++id;
			my_id = id;
		}
	}
	box->Pack(table);
	box->Pack(this->_getButton);
	this->_ressourcesWindow->Add(box);
}

void RessourcesWindow::updateView(std::vector<IEntity *> &ressources)
{
	_content = ressources;
	int compt = 0;
	for (IEntity *u : ressources)
	{
		this->_tableButtons[compt]->SetActive(false);
		this->_tableImages[compt]->SetImage((*ImageSingleton::getInstance().get(u->getType())).copyToImage());
		++compt;
	}
	while (compt != 9)
	{
		this->_tableButtons[compt]->SetActive(false);
		this->_tableButtons[compt]->ClearImage();
		++compt;
	}
}

void RessourcesWindow::clickOnGetButton(GameScreen *game)
{
	//ici on à les ressources que l'on veut drop
	std::vector<IEntity *> drop;
	int compt = 0;

	for (auto u : this->_tableButtons)
	{
		if (u->IsActive() == true)
		{
			game->_inventory->addToInventory(game->getPlayers().front(), this->_content[compt]);
		}
		++compt;
	}
	/*DUMP*/
	std::cout << "Nombre resources drop : " << drop.size() << std::endl;
}

void RessourcesWindow::selectRessource(int pos)
{
	std::cout << "Je clique !! : " << this->_tableButtons[pos]->GetId() << std::endl;

	if (pos > this->_content.size())
		this->_tableButtons[pos]->SetActive(false);
	//this->_tableButtons[pos]->SetState(sfg::Button::State::ACTIVE);
	//sfg::Context::Get().GetEngine().SetProperty("Button#" + this->_tableButtons[pos]->GetId(), "BorderColor", sf::Color(0, 0, 100));	
	//sfg::Context::Get().GetEngine().SetProperty("Button#guess", "BorderColor", sf::Color(0, 100, 0));
	//sfg
	//this->_ressourcesWindow->Refresh();
}

void RessourcesWindow::Show(bool show)
{
	this->_ressourcesWindow->Show(show);
}

void RessourcesWindow::draw()
{
	Singleton::getInstance()._sfgui.Display(*Singleton::getInstance()._window);
}

void RessourcesWindow::update()
{
	Singleton::getInstance()._desktop.Update(0.1f);
}

RessourcesWindow::~RessourcesWindow()
{
}
