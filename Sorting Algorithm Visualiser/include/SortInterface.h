#pragma once
#include <array>
#include <vector>
#include <unordered_map>
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

constexpr int MAX_SIZE = 120;

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
	void ShuffleList();

private:
	void InitList();
	void InitGraph();

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
	sf::Color bar, barSwapping;

	std::unordered_map<std::string, sf::Text> UIElements;

	std::string currentAlgorithm;

	bool isAppRunning;	// track is start button is clicked
	bool sorted;
	bool shuffled;
	int index;			// position of the last red bar that needs turning green
	int counter;
};

inline SortInterface::SortInterface(std::shared_ptr<sf::RenderWindow> window)
	: window(window), 
	bar({66, 237, 209}),			// default bar colour
	barSwapping(sf::Color::Red),	// colour of bar thats current getting changed
	isAppRunning(false),			
	sorted(false),					
	shuffled(false),
	index(0),						// track last bar that was changed (to change its colour back to default)
	counter(0)						
{
	// setup initial values:
	InitList();
	font = util::LoadFont();
	
	// Init UI buttons and their positions:
	// start button:
	UIElements.insert({ 
		"Start", 
		util::SetupText("Start", 
		font, 
		{ 100, 50 }) 
	});
	// current selected algorithm button:
	UIElements.insert({ 
		"Current algorithm selected", 
		util::SetupText("Current algorithm selected: ...", 
		font, 
		{ 100, 80 }) 
	});
	// list sorted button:
	UIElements.insert({ 
		"Sorted",
		util::SetupText("",
		font,
		{ 
			(graph[0].getPosition().x/2.f)/2.f, 
			(float)window->getSize().y-30 
		}, 
		sf::Color::White) 
	});
	// sorting algorithm buttons:
	// Bubble
	UIElements.insert({ 
		"Bubble Sort", 
		util::SetupText("Bubble Sort", 
		font, 
		{ 
			(UIElements["Start"].getPosition().x+UIElements["Start"].getGlobalBounds().width)+100, 
			50 
		}) 
	});
	// Insertion
	UIElements.insert({ 
		"Insertion Sort", 
		util::SetupText("Insertion Sort", 
		font, 
		{ 
			(UIElements["Bubble Sort"].getPosition().x+UIElements["Bubble Sort"].getGlobalBounds().width)+100, 
			50 
		}) 
	});
	// Selection
	UIElements.insert({ 
		"Selection Sort", 
		util::SetupText("Selection Sort", 
		font, 
		{ 
			(UIElements["Insertion Sort"].getPosition().x+UIElements["Insertion Sort"].getGlobalBounds().width)+100, 
			50 
		}) 
	});
	// Merge
	UIElements.insert({ 
		"Merge Sort", 
		util::SetupText("Merge Sort", 
		font, 
		{ 
			(UIElements["Selection Sort"].getPosition().x+UIElements["Selection Sort"].getGlobalBounds().width)+100, 
			50 
		}) 
	});
	// shuffle button:
	UIElements.insert({ 
		"Shuffle", 
		util::SetupText("Shuffle", 
		font, 
		{ 
			(UIElements["Merge Sort"].getPosition().x+UIElements["Merge Sort"].getGlobalBounds().width)+100, 
			50 
		}) 
	});
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
