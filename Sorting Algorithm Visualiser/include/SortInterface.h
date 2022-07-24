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
	sf::Text startBtn, shuffleBtn, listSorted, currentSelectedAlg;
	// sort alg texts:
	sf::Text bubbleSortBtn, insertionSortBtn, selectionSortBtn, mergeSortBtn;

	std::string currentAlgorithm;

	bool isAppRunning;	// track is start button is clicked
	bool sorted;
	bool shuffled;
	int index;			// position of the last red bar that needs turning green

private:
	float barSpacing;	// spacing between each individual bar
	float barWidth;

	float windowX;
	float listWidth;
	float fullGap;
};

inline SortInterface::SortInterface(std::shared_ptr<sf::RenderWindow> window)
	: window(window), 
	isAppRunning(false), 
	sorted(false),
	shuffled(false),
	index(0)
{
	// setup initial values:
	InitList();
	font = util::LoadFont();
	util::SetupText("Start", startBtn, font, 20, sf::Color::Red, { 100, 50 });
	util::SetupText("Current selected algorithm: ...", currentSelectedAlg, font, 16, sf::Color::Red, {100, 80});

	util::SetupText("Bubble Sort", bubbleSortBtn, font, 20, sf::Color::Red, { (startBtn.getPosition().x+startBtn.getGlobalBounds().width)+100, 50 });
	util::SetupText("Insertion Sort", insertionSortBtn, font, 20, sf::Color::Red, { (bubbleSortBtn.getPosition().x+bubbleSortBtn.getGlobalBounds().width)+100, 50 });
	util::SetupText("Selection Sort", selectionSortBtn, font, 20, sf::Color::Red, { (insertionSortBtn.getPosition().x+insertionSortBtn.getGlobalBounds().width)+100, 50 });
	util::SetupText("Merge Sort", mergeSortBtn, font, 20, sf::Color::Red, { (selectionSortBtn.getPosition().x+selectionSortBtn.getGlobalBounds().width)+100, 50 });

	util::SetupText("Shuffle", shuffleBtn, font, 20, sf::Color::White, { (mergeSortBtn.getPosition().x+mergeSortBtn.getGlobalBounds().width)+100, 50 });
	util::SetupText("", listSorted, font, 20, sf::Color::White, { (graph[0].getPosition().x/2.f)/2.f, (float)window->getSize().y-30 });
}

inline void SortInterface::ShuffleList()
{
	std::shuffle(randomNumberList.begin(), randomNumberList.end(), std::mt19937{ std::random_device{}() });
	// assign randomNumberList values to corresponding index from graph list
	InitGraph();
}

inline void SortInterface::InitList()
{
	// generate random number between 1-500 to represent each bar:
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<u32> generate(5, 500);

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
