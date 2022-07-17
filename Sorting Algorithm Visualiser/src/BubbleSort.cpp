#include "../include/BubbleSort.h"

BubbleSort::BubbleSort(sf::RenderWindow* window)
	: SortInterface(window), started(false) 
{}

// bubble sort algorithm
void BubbleSort::Sort(std::array<uint32_t, MAX_SIZE>& randomNumberList, 
		std::array<sf::RectangleShape, MAX_SIZE>& graph, 
		const int& listSize)
{
	for (int i = listSize-1; i > 0; i--) 
	{
		for (int j = listSize-1; j > 0; j--)
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
				return;
			}
		}
		graph[i].setFillColor(sf::Color::Green);
	}
}

BubbleSort::~BubbleSort() {}

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
			if (startBtn.getGlobalBounds().contains(window->mapPixelToCoords(sf::Mouse::getPosition(*window))))
			{
				std::cout << "start button clicked.\n";
				startBtn.setString("");
				started = true;
			}
			break;
		}
	}
	if (started)
		Sort(randomNumberList, graph, listSize);
}

void BubbleSort::Render() 
{
	window->draw(startBtn);
	for (const auto& value : graph)
		window->draw(value);
}