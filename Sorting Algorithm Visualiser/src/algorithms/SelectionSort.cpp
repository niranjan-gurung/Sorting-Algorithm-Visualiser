#include "../../include/SelectionSort.h"

SelectionSort::SelectionSort(std::shared_ptr<sf::RenderWindow> window) 
	: SortInterface(window) {}

// Selection sort algorithm:
void SelectionSort::Sort(
	std::array<u32, MAX_SIZE>& randomNumberList, 
	std::array<Rect, MAX_SIZE>& graph)
{
	bool swapped = false;
	for (int i = 0; i < MAX_SIZE-1; i++)
	{
		u32 minIndex = i;
		for (int j = i+1; j < MAX_SIZE; j++)
		{
			if (randomNumberList[j] < randomNumberList[minIndex])
			{
				minIndex = j;
				swapped = true;
			}
		}
		graph[minIndex].setFillColor(barSwapping);
		// swap from the numbers list:
		std::swap(randomNumberList[minIndex], randomNumberList[i]);
		// swap bar from graph list:
		std::swap(graph[minIndex], graph[i]);

		float xCoord = graph[i].getPosition().x;
		graph[i].setPosition(
			graph[minIndex].getPosition().x, 
			graph[i].getPosition().y
		);
		graph[minIndex].setPosition(
			xCoord, 
			graph[minIndex].getPosition().y
		);
		graph[minIndex].setFillColor(bar);

		index = i;
		if (swapped)
			return;
	}
}

void SelectionSort::Update()
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
				if (std::is_sorted(randomNumberList.begin(), randomNumberList.end()))
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
				//sorted = false;
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

			//sorted = true;
			shuffled = false;
			isAppRunning = false;
		}
	}
}

void SelectionSort::Render()
{
	// draw all UI texts:
	for (const auto& value : UIElements)
		window->draw(value.second);

	for (const auto& value : graph)
		window->draw(value);
}

SelectionSort::~SelectionSort() {}