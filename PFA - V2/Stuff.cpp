#include "Stuff.h"


Stuff::Stuff()
{
	this->_selectedRessource = NULL;
	this->_isInStuffScroll = false;
	createWindow();
	createToolbar();
}

void Stuff::createWindow()
{
	this->_stuffWindow = sfg::Window::Create(sfg::Window::Style::TITLEBAR | sfg::Window::Style::BACKGROUND);
	this->_stuffWindow->Show(false);
	this->_stuffWindow->SetTitle("Stuff");
	this->_stuffWindow->SetPosition(sf::Vector2f(1300.f, 400.f));
	this->_mainBox = sfg::Box::Create(sfg::Box::Orientation::VERTICAL);
	this->_stuffBox = sfg::Box::Create(sfg::Box::Orientation::VERTICAL);
	
	this->_scroll = sfg::ScrolledWindow::Create();

	this->_scroll->SetScrollbarPolicy(sfg::ScrolledWindow::VERTICAL_ALWAYS | sfg::ScrolledWindow::HORIZONTAL_NEVER);
	this->_scroll->AddWithViewport(this->_stuffBox);

	this->_scroll->GetSignal(sfg::Widget::OnMouseEnter).Connect(std::bind(&Stuff::mousePos, this, true));
	this->_scroll->GetSignal(sfg::Widget::OnMouseLeave).Connect(std::bind(&Stuff::mousePos, this, false));

	// Always remember to set the minimum size of a ScrolledWindow.
	this->_scroll->SetRequisition(sf::Vector2f(280.f, 550.f));
	this->_mainBox->Pack(this->_scroll, true, true);
	this->_stuffWindow->Add(this->_mainBox);
	Singleton::getInstance()._desktop.Add(this->_stuffWindow);
}

void Stuff::createToolbar()
{
	this->_toolbar = sfg::Box::Create(sfg::Box::Orientation::VERTICAL);
	auto deleteButton = sfg::Button::Create("Supprimer de la table");
	deleteButton->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&Stuff::deleteClick, this));
	this->_toolbar->Pack(deleteButton);
	this->_mainBox->PackEnd(this->_toolbar);
}

void Stuff::deleteClick()
{
	if (this->_selectedRessource != NULL)
	{
		//TODO faire quelque chose
	}
}

void Stuff::mousePos(bool pos)
{
	this->_isInStuffScroll = pos;
}

void Stuff::checkScrollEvent()
{
	if (this->_isInStuffScroll == true && Singleton::getInstance().deltaMouseWeel != 0)
	{
		if (Singleton::getInstance().deltaMouseWeel > 0)
			this->_scroll->GetVerticalAdjustment()->SetValue(this->_scroll->GetVerticalAdjustment()->GetValue() - 60);
		else
			this->_scroll->GetVerticalAdjustment()->SetValue(this->_scroll->GetVerticalAdjustment()->GetValue() + 60);
	}
	Singleton::getInstance().deltaMouseWeel = 0;
}

void Stuff::createZones(std::vector<Player *>&players)
{
	this->_players = players;
	for (Player *u : players)
	{
		createCompartment(u);
	}
}


void Stuff::createCompartment(Player *player)
{
	int compt = 0;
	auto box = sfg::Box::Create(sfg::Box::Orientation::VERTICAL);

	auto table = sfg::Table::Create();
	CustomToggleButton *but1 = new CustomToggleButton(player, NULL);
	but1->_button->SetRequisition(sf::Vector2f(180.f, 166.f));
	but1->_button->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&Stuff::mouseLeftPress, this, but1));
	this->_tableButtons.push_back(but1);
	table->Attach(but1->_box, sf::Rect<sf::Uint32>(0, 0, 1, 1), sfg::Table::FILL | sfg::Table::EXPAND, sfg::Table::FILL, sf::Vector2f(10.f, 10.f));
	
	CustomToggleButton *but2 = new CustomToggleButton(player, NULL);
	but2->_button->SetRequisition(sf::Vector2f(180.f, 166.f));
	but2->_button->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&Stuff::mouseLeftPress, this, but2));
	this->_tableButtons.push_back(but2);
	table->Attach(but2->_box, sf::Rect<sf::Uint32>(1, 0, 1, 1), sfg::Table::FILL | sfg::Table::EXPAND, sfg::Table::FILL, sf::Vector2f(10.f, 10.f));

	CustomToggleButton *but3 = new CustomToggleButton(player, NULL);
	but3->_button->SetRequisition(sf::Vector2f(180.f, 166.f));
	but3->_button->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&Stuff::mouseLeftPress, this, but3));
	this->_tableButtons.push_back(but3);
	table->Attach(but3->_box, sf::Rect<sf::Uint32>(2, 0, 1, 1), sfg::Table::FILL | sfg::Table::EXPAND, sfg::Table::FILL, sf::Vector2f(10.f, 10.f));
	
	box->PackStart(sfg::Label::Create(player->getName()));
	box->PackEnd(table);
	this->_tables.push_back(table);
	this->_tableBox.push_back(box);
	this->_stuffBox->PackEnd(box);
}

void Stuff::mouseLeftPress(CustomToggleButton *)
{

}

void Stuff::Show(bool show)
{
	this->_stuffWindow->Show(show);
}

void Stuff::showBox(std::vector<Player *>&players)
{
	int compt = 0;
	while (compt < players.size())
	{
		if (this->_tableBox[compt]->IsLocallyVisible() == true && players[compt]->getSelected() == false)
		{
			this->_stuffBox->Remove(this->_tableBox[compt]);
			this->_tableBox[compt]->Show(false);
		}
		else if (this->_tableBox[compt]->IsLocallyVisible() == false && players[compt]->getSelected() == true)
		{
			this->_stuffBox->Pack(this->_tableBox[compt]);
			this->_tableBox[compt]->Show(true);
		}
		++compt;
	}
	this->_scroll->Refresh();
}

Stuff::~Stuff()
{
}
