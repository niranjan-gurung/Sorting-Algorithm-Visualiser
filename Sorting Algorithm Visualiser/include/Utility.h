#pragma once

#include "SFML\Graphics.hpp"
#include <string>
#include <iostream>

struct util 
{
	static void LoadFont(sf::Font& font)
	{
		if (!font.loadFromFile("./font/arial.ttf"))
			std::cout << "Couldn't load font.." << std::endl;
	}

	static void SetupText(sf::Text& text, const std::string& name,
		sf::Font& font, int charSize, sf::Color colour)
	{
		text.setFont(font);
		text.setCharacterSize(charSize);
		text.setFillColor(colour);
		text.setString(name);
		text.setOrigin(text.getGlobalBounds().width/2, text.getGlobalBounds().height/2);
		text.setPosition(100, 50);
	}
};