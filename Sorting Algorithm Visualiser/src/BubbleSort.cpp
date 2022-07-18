#include "../include/BubbleSort.h"

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
	}
}

void BubbleSort::Render() 
{
	window->draw(startBtn);
	for (const auto& value : graph)
		window->draw(value);
}

BubbleSort::~BubbleSort() {}