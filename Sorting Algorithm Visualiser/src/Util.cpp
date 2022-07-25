#include "../include/Util.h"

namespace util 
{
	sf::Font LoadFont()
	{
		sf::Font font;
		if (!font.loadFromFile("./font/arial.ttf"))
			std::cout << "Couldn't load font.." << std::endl;
		return font;
	}

	sf::Text SetupText(const std::string& name, 
			sf::Font& font, 
			const sf::Vector2f& pos,
			sf::Color colour,
			int charSize) 
	{
		sf::Text text;
		text.setFont(font);
		text.setCharacterSize(charSize);
		text.setFillColor(colour);
		text.setString(name);
		text.setPosition(pos.x, pos.y);
		return text;
	}
}