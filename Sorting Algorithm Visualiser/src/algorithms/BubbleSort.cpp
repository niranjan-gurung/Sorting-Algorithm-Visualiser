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
			graph[j].setFillColor(bar);
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
				graph[j].setFillColor(barSwapping);
				index = j;
				return;
			}
		}
	}
}

void BubbleSort::Update(sf::Clock& dt, util::Settings& settings) 
{
	while (window->pollEvent(event))
	{
		ImGui::SFML::ProcessEvent(event);
		switch (event.type)
		{
		case sf::Event::Closed:
			window->close();
			break;
		}
	}
	ImGui::SFML::Update(*window, dt.restart());

	// reinitialise list with new values:
	if (settings.generateNewList)
	{
		InitList();
		settings.generateNewList = false;
		settings.isSorted = true;
	}
	
	// shuffle list:
	if (settings.isShuffled)
	{
		ShuffleList();
		settings.isShuffled = false;
		settings.isSorted = false;
	}

	if (settings.isAppRunning && !settings.isShuffled)
	{
		Sort(randomNumberList, graph);

		// enter once list is fully sorted:
		if (std::is_sorted(randomNumberList.begin(), randomNumberList.end()))
		{
			graph[index].setFillColor(bar);
			settings.isSorted = true;
			settings.isShuffled = false;
			settings.isAppRunning = false;
		}
	}
}

void BubbleSort::Render() 
{
	for (const auto& value : graph)
		window->draw(value);
}

BubbleSort::~BubbleSort() {}