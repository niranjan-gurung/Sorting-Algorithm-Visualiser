#pragma once

#include "SFML\Graphics.hpp"
#include <string>
#include <iostream>

namespace util {

	sf::Font LoadFont();
	sf::Text SetupText(const std::string& name,	
			sf::Font& font, 
			int charSize, 
			sf::Color colour, 
			const sf::Vector2f& pos);
};