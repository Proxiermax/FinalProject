#include "menu.h"

Menu::Menu(float width, float height)
{
	if (!font.loadFromFile("Texts/Roboto-Bold.ttf")); {
		//handle error
	}

	menu[0].setFont(font);
	menu[0].setCharacterSize(60);
	menu[0].setFillColor(sf::Color::Red);
	menu[0].setString("PLAY");
	menu[0].setOutlineThickness(3);
	menu[0].setOutlineColor(sf::Color::Black);
	menu[0].setOrigin(menu[0].getGlobalBounds().width / 2,
		menu[0].getGlobalBounds().height / 2);
	menu[0].setPosition(sf::Vector2f(width / 2,
		height / (maxItems + 1) * 1));

	menu[1].setFont(font);
	menu[1].setCharacterSize(40);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("LeaderBoard");
	menu[1].setOutlineThickness(3);
	menu[1].setOutlineColor(sf::Color::Black);
	menu[1].setOrigin(menu[1].getGlobalBounds().width / 2,
		menu[1].getGlobalBounds().height / 2);
	menu[1].setPosition(sf::Vector2f(width / 2,
		height / (maxItems + 1) * 2));

	menu[2].setFont(font);
	menu[2].setCharacterSize(40);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("EXIT");
	menu[2].setOutlineThickness(3);
	menu[2].setOutlineColor(sf::Color::Black);
	menu[2].setOrigin(menu[2].getGlobalBounds().width / 2,
		menu[2].getGlobalBounds().height / 2);
	menu[2].setPosition(sf::Vector2f(width / 2,
		height / (maxItems + 1) * 3));
}

Menu::~Menu()
{

}

void Menu::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < maxItems; i++) {
		window.draw(menu[i]);
	}

}

void Menu::MoveUp()
{
	if (selectedItem - 1 >= 0) {
		menu[selectedItem].setFillColor(sf::Color::White);
		selectedItem--;
		menu[selectedItem].setFillColor(sf::Color::Red);
	}
}

void Menu::MoveDown()
{
	if (selectedItem + 1 < maxItems) {
		menu[selectedItem].setFillColor(sf::Color::White);
		selectedItem++;
		menu[selectedItem].setFillColor(sf::Color::Red);
	}
}

int Menu::getPressItem()
{
	return selectedItem;
}