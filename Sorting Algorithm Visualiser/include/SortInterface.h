#pragma once
#include <array>
#include <vector>
#include <random>
#include <algorithm>

#include "Util.h"

/* Abstract class:
 * 
 * Initialises randomNumberList and graph to hold a list of shuffled values
 * Setup start button/text
 * Update and Render methods needs appropriately implementing in subsequent classes
 * Dummy impl for the two Sort() methods to avoid conflicts:
	(as mergesort has different params compared to the other sorting algorithms):
 */

constexpr int MAX_SIZE = 100;

using u32 = uint32_t;
using Rect = sf::RectangleShape;

class SortInterface
{
public:
	SortInterface(std::shared_ptr<sf::RenderWindow> window);
	virtual ~SortInterface() = default;

	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Sort(
		std::array<u32, MAX_SIZE>& randomNumberList, 
		std::array<Rect, MAX_SIZE>& graph);
	// function overload for merge sort:
	virtual void Sort(
		std::array<u32, MAX_SIZE>& randomNumberList, 
		std::array<Rect, MAX_SIZE>& graph,  
		int left, 
		int right,
		bool& merged);

protected:
	std::shared_ptr<sf::RenderWindow> window;
	sf::Event event;

	/* empty lists: 
	 * randomNumberList = number representing a bar.
	 * graph = bar that visualises the corresponding number from randomNumberList.
	 */
	std::array<u32, MAX_SIZE> randomNumberList;
	std::array<Rect, MAX_SIZE> graph;

	// utility
	sf::Font font;
	sf::Text startBtn;

	bool isAppRunning;	// track is start button is clicked
	int index;			// position of the last red bar that needs turning green

private:
	void SetupList();
};

inline SortInterface::SortInterface(std::shared_ptr<sf::RenderWindow> window)
	: window(window), 
	isAppRunning(false), 
	index(0)
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
	std::uniform_int_distribution<u32> generate(5, 500);

	float barSpacing = 5.f;	// tracks spacing between each individual graph's bars
	float barWidth = 5.f;
	
	// init list values:
	for (auto& value : randomNumberList)
	{
		value = generate(rng);
	}

	// shuffle list:
	//std::shuffle(randomNumberList.begin(), randomNumberList.end(), std::mt19937{ std::random_device{}() });

	float windowX = (float)window->getSize().x;
	float listWidth = (barWidth*MAX_SIZE) + (barSpacing*MAX_SIZE);
	float fullGap = windowX-listWidth;

	// assign randomNumberList values to corresponding index from graph list:
	for (int i = 0; i < MAX_SIZE; i++)
	{
		graph[i] = Rect(sf::Vector2f(barWidth, randomNumberList[i]));
		graph[i].setFillColor(sf::Color::Green);
		if (i == 0)
		{
			graph[i].setPosition(
				(fullGap/2.f)+barSpacing, 
				window->getSize().y-graph[i].getGlobalBounds().height
			);
			barSpacing = (fullGap/2.f)+barSpacing;
		}
		else
		{
			graph[i].setPosition(
				barSpacing, 
				window->getSize().y-graph[i].getGlobalBounds().height
			);
			barSpacing += 10.f;
		}
	}
}

// empty implementation (needed to not conflict with mergesort function):
inline void SortInterface::Sort(
	std::array<u32, MAX_SIZE>& randomNumberList, 
	std::array<Rect, MAX_SIZE>& graph) {}

inline void SortInterface::Sort(
	std::array<u32, MAX_SIZE>& randomNumberList, 
	std::array<Rect, MAX_SIZE>& graph, 
	int left, 
	int right,
	bool& merged) {}
