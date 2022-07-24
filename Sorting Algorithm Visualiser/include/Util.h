#pragma once

#include "SFML\Graphics.hpp"
#include <string>
#include <iostream>

namespace util {

	sf::Font LoadFont();
	void SetupText(const std::string& name,	
			sf::Text& text,
			sf::Font& font, 
			int charSize, 
			sf::Color colour, 
			const sf::Vector2f& pos);
};