#pragma once

#include "SFML\Graphics.hpp"
#include <string>
#include <iostream>

namespace util {

	sf::Font LoadFont();
	sf::Text SetupText(const std::string& name,	
			sf::Font& font, 
			const sf::Vector2f& pos = { 50, 50 },
			sf::Color colour = sf::Color::Red,
			int charSize = 20);
};