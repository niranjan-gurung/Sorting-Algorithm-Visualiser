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

void SelectionSort::Update(sf::Clock& dt, util::Settings& settings)
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

void SelectionSort::Render()
{
	for (const auto& value : graph)
		window->draw(value);
}

SelectionSort::~SelectionSort() {}