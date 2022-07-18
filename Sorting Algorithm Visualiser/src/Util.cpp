#include "../include/Util.h"

namespace util 
{
	void LoadFont(sf::Font& font)
	{
		if (!font.loadFromFile("./font/arial.ttf"))
			std::cout << "Couldn't load font.." << std::endl;
	}

	void SetupText(sf::Text& text, const std::string& name, 
			sf::Font& font, int charSize, sf::Color colour)
	{
		text.setFont(font);
		text.setCharacterSize(charSize);
		text.setFillColor(colour);
		text.setString(name);
		text.setOrigin(text.getGlobalBounds().width/2, text.getGlobalBounds().height/2);
		text.setPosition(100, 50);
	}
}