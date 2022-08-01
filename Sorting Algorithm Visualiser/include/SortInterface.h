#pragma once
#include "../imgui/imgui.h"
#include "../imgui/imgui-SFML.h"

#include "Util.h"

#include <array>
#include <vector>
#include <unordered_map>
#include <random>
#include <algorithm>

/* Abstract class:
 * 
 * Initialises randomNumberList and graph to hold a list of shuffled values
 * Setup start button/text
 * Update and Render methods needs appropriately implementing in subsequent classes
 * Dummy impl for the two Sort() methods to avoid conflicts:
	(as mergesort has different params compared to the other sorting algorithms):
 */

constexpr int MAX_SIZE = 120;
static const char* algorithmList[] = { 
	"Bubble Sort", "Insertion Sort", "Selection Sort", "Merge Sort" 
};

using u32	= uint32_t;
using Rect	= sf::RectangleShape;

class SortInterface
{
public:
	SortInterface(std::shared_ptr<sf::RenderWindow> window);
	virtual ~SortInterface() = default;

	virtual void Update(sf::Clock& dt) = 0;
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
	void ShuffleList();

private:
	void InitList();
	void InitGraph();

protected:
	std::shared_ptr<sf::RenderWindow> window;
	sf::Event event;

	std::shared_ptr<SortInterface> currentAlgorithm;

	/* empty lists: 
	 * randomNumberList = number representing a bar.
	 * graph = bar that visualises the corresponding number from randomNumberList.
	 */
	std::array<u32, MAX_SIZE> randomNumberList;
	std::array<Rect, MAX_SIZE> graph;

	// utility
	sf::Font font;
	sf::Color bar, barSwapping;

	bool isAppRunning;	// track is start button is clicked
	bool sorted;
	bool shuffled;
	int index;			// position of the last red bar that needs turning green
	int selected;		// track current algorithm thats selected
};

inline SortInterface::SortInterface(std::shared_ptr<sf::RenderWindow> window)
	: window(window), 
	currentAlgorithm(nullptr),
	bar({66, 237, 209}),			// default bar colour
	barSwapping(sf::Color::Red),	// colour of bar thats current getting changed
	isAppRunning(false),			
	sorted(true),					// list is already sorted when app is initially started
	shuffled(false),
	index(0),						// track last bar that was changed (to change its colour back to default)
	selected(0)
{
	// setup initial values:
	InitList();
	font = util::LoadFont();
}

inline void SortInterface::ShuffleList()
{
	std::shuffle(randomNumberList.begin(), randomNumberList.end(), std::mt19937{ std::random_device{}() });
	// assign randomNumberList values to corresponding index from graph list
	InitGraph();
}

inline void SortInterface::InitList()
{
	float windowY = (float)window->getSize().y;

	// generate random number between 1-500 to represent each bar:
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<u32> generate(5, windowY);

	// init list values:
	for (auto& value : randomNumberList)
		value = generate(rng);

	// present sorted graph when app is initially started
	std::sort(randomNumberList.begin(), randomNumberList.end());
	
	// assign randomNumberList values to corresponding index from graph list:
	InitGraph();
}

inline void SortInterface::InitGraph()
{
	float barSpacing = 5.f;	// spacing between each individual bar
	float barWidth = 5.f;

	// values used to center entire graph:
	float windowX = (float)window->getSize().x;
	float listWidth = (barWidth*MAX_SIZE) + (barSpacing*MAX_SIZE);
	float fullGap = windowX-listWidth;

	for (int i = 0; i < MAX_SIZE; i++)
	{
		graph[i] = Rect(sf::Vector2f(barWidth, randomNumberList[i]));
		graph[i].setFillColor(sf::Color(66, 237, 209));
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
