#include "../../include/BubbleSort.h"

BubbleSort::BubbleSort(std::shared_ptr<sf::RenderWindow> window)
	: SortInterface(window) {}

// Bubble sort algorithm:
void BubbleSort::Sort(
	std::array<u32, MAX_SIZE>& randomNumberList, 
	std::array<Rect, MAX_SIZE>& graph)
{
	for (int i = MAX_SIZE-1; i > 0; i--) 
	{
		for (int j = MAX_SIZE-1; j > 0; j--)
		{
			graph[j].setFillColor(sf::Color::Green);
			if (randomNumberList[j] < randomNumberList[j-1])
			{
				// swap from the numbers list:
				std::swap(randomNumberList[j], randomNumberList[j-1]);
				// swap bar from graph list:
				std::swap(graph[j], graph[j-1]);

				float xCoord = graph[j].getPosition().x;
				graph[j].setPosition(
					graph[j-1].getPosition().x, 
					graph[j].getPosition().y
				);
				graph[j-1].setPosition(
					xCoord, 
					graph[j-1].getPosition().y
				);
				graph[j].setFillColor(sf::Color::Red);
				index = j;
				return;
			}
		}
	}
}

void BubbleSort::Update() 
{
	while (window->pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window->close();
			break;

		case sf::Event::MouseButtonPressed:

			// start sorting:
			if (startBtn.getGlobalBounds().contains(
				window->mapPixelToCoords(
					sf::Mouse::getPosition(*window))))
			{
				if (std::is_sorted(randomNumberList.begin(), randomNumberList.end()))
				{
					std::cout << "List already sorted.\n";
					break;
				}
				
				std::cout << "start button clicked.\n";
				
				startBtn.setString("");
				currentSelectedAlg.setString("");
				bubbleSortBtn.setString("");
				insertionSortBtn.setString("");
				selectionSortBtn.setString("");
				mergeSortBtn.setString("");
				shuffleBtn.setString("");
				isAppRunning = true;
			}

			// shuffle list:
			if (shuffleBtn.getGlobalBounds().contains(
				window->mapPixelToCoords(
					sf::Mouse::getPosition(*window))))
			{
				std::cout << "shuffle button clicked.\n";
				
				ShuffleList();
				listSorted.setString("");
				shuffled = true;
				sorted = false;
			}
			break;
		}
	}

	if (isAppRunning && shuffled)
	{
		Sort(randomNumberList, graph);
		if (std::is_sorted(randomNumberList.begin(), randomNumberList.end()))
		{
			graph[index].setFillColor(sf::Color::Green);
			
			// show start button again once sorting animation has finished:
			startBtn.setString("Start");
			currentSelectedAlg.setString("Current selected algorithm: ...");
			bubbleSortBtn.setString("Bubble Sort");
			insertionSortBtn.setString("Insertion Sort");
			selectionSortBtn.setString("Selection Sort");
			mergeSortBtn.setString("Merge Sort");
			shuffleBtn.setString("Shuffle");
			listSorted.setString("Sorted");

			sorted = true;
			isAppRunning = false;
		}
	}
}

void BubbleSort::Render() 
{
	window->draw(startBtn);
	window->draw(currentSelectedAlg);
	window->draw(bubbleSortBtn);
	window->draw(insertionSortBtn);
	window->draw(selectionSortBtn);
	window->draw(mergeSortBtn);
	window->draw(shuffleBtn);

	if (sorted)
		window->draw(listSorted);
	for (const auto& value : graph)
		window->draw(value);
}

BubbleSort::~BubbleSort() {}