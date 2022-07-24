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
		graph[i].setFillColor(sf::Color::Red);
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
			graph[i].setFillColor(sf::Color::Green);
			index = j;
			return;
		}
		graph[j].setFillColor(sf::Color::Green);
	}
}

void InsertionSort::Update()
{
	/*while (window->pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window->close();
			break;

		case sf::Event::MouseButtonPressed:
			if (startBtn.getGlobalBounds().contains(
				window->mapPixelToCoords(
					sf::Mouse::getPosition(*window))))
			{
				std::cout << "start button clicked.\n";
				startBtn.setString("");
				isAppRunning = true;
			}
			break;
		}
	}

	if (isAppRunning)
	{
		Sort(randomNumberList, graph);
		if (std::is_sorted(randomNumberList.begin(), randomNumberList.end()))
		{
			graph[index].setFillColor(sf::Color::Green);
			isAppRunning = false;
		}
	}*/
}

void InsertionSort::Render()
{
	//window->draw(startBtn);
	//for (const auto& value : graph)
	//	window->draw(value);
}

InsertionSort::~InsertionSort() {}