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

	void SetupText(const std::string& name, 
			sf::Text& text, 
			sf::Font& font, 
			int charSize, 
			sf::Color colour, 
			const sf::Vector2f& pos)
	{
		text.setFont(font);
		text.setCharacterSize(charSize);
		text.setFillColor(colour);
		text.setString(name);
		text.setPosition(pos.x, pos.y);
	}
}