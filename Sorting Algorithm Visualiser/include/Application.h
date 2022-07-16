#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <array>
#include <random>
#include <algorithm>

constexpr int MAX_SIZE = 80;

class Application
{
public:
	Application();
	~Application();

	void Run();
	void Update();
	void Render();

private:
    void BubbleSort(std::array<uint32_t, MAX_SIZE>& randomNumberList, 
                    std::array<sf::RectangleShape, MAX_SIZE>& graph, 
                    const int& listSize);

private:
	sf::RenderWindow appWindow;
	sf::Event event;

	sf::Font font;
	sf::Text startBtn;

	std::array<uint32_t, MAX_SIZE> randomNumberList;
	std::array<sf::RectangleShape, MAX_SIZE> graph;

	int barHeight = 8;
	int barGraphSpacing = 15;     // tracks spacing between each individual graph's bars.

	bool started = false;

	// size alias:
	const int listSize = randomNumberList.size();
};