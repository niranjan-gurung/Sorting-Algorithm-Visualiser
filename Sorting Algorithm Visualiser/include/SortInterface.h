#pragma once
#include <SFML/Graphics.hpp>
#include <array>
#include <algorithm>
#include <random>
#include <iostream>

#include "Utility.h"

constexpr int MAX_SIZE = 80;

class SortInterface
{
public:
	SortInterface(sf::RenderWindow* window);
	virtual ~SortInterface() = default;

	virtual void Update() = 0;
	virtual void Render() = 0;

protected:
	sf::RenderWindow* window;
	sf::Event event;

	/* empty lists: 
	 * randomNumberList = number representing a bar
	 * graph = bar that visualises the corresponding number from randomNumberList.
	 */
	std::array<uint32_t, MAX_SIZE> randomNumberList;
	std::array<sf::RectangleShape, MAX_SIZE> graph;
	const int listSize;

	// utility
	sf::Font font;
	sf::Text startBtn;

private:
	void SetupList();
};

inline SortInterface::SortInterface(sf::RenderWindow* window)
	: window(window), listSize(randomNumberList.size())
{
	SetupList();
	util::LoadFont(font);
	util::SetupText(startBtn, "Start!", font, 20, sf::Color::Red);
}

inline void SortInterface::SetupList()
{
	// generate random number between 1-500 to represent each bar:
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<uint32_t> generate(1, 500);

	int barHeight = 8;
	int barGraphSpacing = 15;	// tracks spacing between each individual graph's bars.
	
	// init list values:
	for (auto& value : randomNumberList)
	{
		value = barHeight;
		barHeight += 8;
	}

	// shuffle list:
	std::shuffle(randomNumberList.begin(), randomNumberList.end(), std::mt19937{ std::random_device{}() });

	// assign randomNumberList values to corresponding index from graph list:
	for (int i = 0; i < randomNumberList.size(); i++)
	{
		graph[i] = sf::RectangleShape(sf::Vector2f(10.f, randomNumberList[i]));
		graph[i].setFillColor(sf::Color::Green);
		graph[i].setPosition(
			barGraphSpacing, 
			window->getSize().y-graph[i].getGlobalBounds().height
		);
		barGraphSpacing += 15;
	}
}