#include "InventoryWindow.h"
#include <iostream>


InventoryWindow::InventoryWindow()
{
	createWindow();
}

void InventoryWindow::createWindow()
{
	this->_inventoryWindow = sfg::Window::Create(sfg::Window::Style::TITLEBAR | sfg::Window::Style::BACKGROUND);
	this->_inventoryWindow->SetRequisition(sf::Vector2f(500, 300.0f));
	this->_inventoryWindow->SetTitle("Inventory");
	this->_numberWindow = nullptr;
	this->_desktop.Add(this->_inventoryWindow);
}

void InventoryWindow::createTabs(std::vector<Player *>&players)
{
	this->_noteBook = sfg::Notebook::Create();
	auto bou = sfg::Button::Create();
	this->_noteBook->AppendPage(bou, sfg::Label::Create("Prout"));
	for (Player *u : players)
	{
		std::cout << "PPPPPPPPPPPPDEKF?EKF?EKF?EKF?EK" << std::endl;
		_noteBook->AppendPage(u->_book, sfg::Label::Create(u->getName()));
	}
	_noteBook->SetScrollable(true);
	_noteBook->SetRequisition(sf::Vector2f(200.f, 0.f));
	this->_inventoryWindow->Add(_noteBook);
}

void InventoryWindow::createCompartment(Player *player)
{
	//on crée la structure
	auto boxmain = sfg::Box::Create(sfg::Box::Orientation::VERTICAL);
	auto table = sfg::Table::Create();
	for (int i = 0; i < 3; i++)
	{

		for (int j = 0; j < 3; j++)
		{
			auto  tmp = sfg::Image::Create();
			tmp->SetImage(this->_img);
			table->Attach(tmp, sf::Rect<sf::Uint32>(i, j, 1, 1), sfg::Table::FILL | sfg::Table::EXPAND, sfg::Table::FILL, sf::Vector2f(0.f, 0.f));
		}
	}
	boxmain->Pack(table, false);
	_noteBook->AppendPage(boxmain, sfg::Label::Create("New Player"));
	this->_inventoryWindow->Add(_noteBook);

}
void InventoryWindow::init()
{
	this->_img.loadFromFile("carre.png");
}

void InventoryWindow::update()
{
	_desktop.Update(Singleton::getInstance()._clock->restart().asSeconds());
}

void InventoryWindow::draw()
{
	Singleton::getInstance()._sfgui.Display(*Singleton::getInstance()._window);
}

InventoryWindow::~InventoryWindow()
{
}
