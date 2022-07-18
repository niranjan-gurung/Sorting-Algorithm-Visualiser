#pragma once

#include "SFML\Graphics.hpp"
#include <string>
#include <iostream>

namespace util 
{
	void LoadFont(sf::Font& font);
	void SetupText(sf::Text& text, const std::string& name,
		sf::Font& font, int charSize, sf::Color colour);
};