#include "../../include/InsertionSort.h"

InsertionSort::InsertionSort(std::shared_ptr<sf::RenderWindow> window)
	: SortInterface(window) {}

// Insertion sort algorithm:
void InsertionSort::Sort(
	std::array<u32, MAX_SIZE>& randomNumberList, 
	std::array<Rect, MAX_SIZE>& graph)
{
	for (int i = 1; i < MAX_SIZE; i++)
	{
		graph[i].setFillColor(barSwapping);
		u32 key = randomNumberList[i];
		int j = i-1;
		while (j >= 0 && randomNumberList[j] > key)
		{
			// swap from the numbers list:
			std::swap(randomNumberList[j], randomNumberList[j+1]);
			// swap bar from graph list:
			std::swap(graph[j], graph[j+1]);

			float xCoord = graph[j].getPosition().x;
			graph[j].setPosition(
				graph[j+1].getPosition().x, 
				graph[j].getPosition().y
			);
			graph[j+1].setPosition(
				xCoord, 
				graph[j+1].getPosition().y
			);
			graph[i].setFillColor(bar);
			index = j;
			return;
		}
		graph[j].setFillColor(bar);
	}
}

void InsertionSort::Update()
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
			if (UIElements["Start"].getGlobalBounds().contains(
				window->mapPixelToCoords(
					sf::Mouse::getPosition(*window))))
			{
				if (sorted)
				{
					std::cout << "List already sorted.\n";
					break;
				}
				std::cout << "start button clicked.\n";

				// set all Texts to empty string:
				for (auto& it : UIElements)
					it.second.setString("");

				isAppRunning = true;
			}

			// shuffle list:
			if (UIElements["Shuffle"].getGlobalBounds().contains(
				window->mapPixelToCoords(
					sf::Mouse::getPosition(*window))))
			{
				std::cout << "shuffle button clicked.\n";

				ShuffleList();

				UIElements["Sorted"].setString("");
				shuffled = true;
				sorted = false;
			}
			break;
		}
	}

	if (isAppRunning && shuffled)
	{
		Sort(randomNumberList, graph);

		// enter once list is fully sorted:
		if (std::is_sorted(randomNumberList.begin(), randomNumberList.end()))
		{
			graph[index].setFillColor(bar);

			// show start button again once sorting animation has finished:
			UIElements["Start"].setString("Start");
			UIElements["Current selected algorithm: ..."].setString("Current selected algorithm: ...");
			UIElements["Bubble Sort"].setString("Bubble Sort");
			UIElements["Insertion Sort"].setString("Insertion Sort");
			UIElements["Selection Sort"].setString("Selection Sort");
			UIElements["Merge Sort"].setString("Merge Sort");
			UIElements["Shuffle"].setString("Shuffle");
			UIElements["Sorted"].setString("Sorted");

			sorted = true;
			shuffled = false;
			isAppRunning = false;
		}
	}
}

void InsertionSort::Render()
{
	// draw all UI texts:
	for (const auto& value : UIElements)
		window->draw(value.second);

	for (const auto& value : graph)
		window->draw(value);
}

InsertionSort::~InsertionSort() {}