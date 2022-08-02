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

void InsertionSort::Update(sf::Clock& dt, util::Settings& settings)
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

void InsertionSort::Render()
{
	for (const auto& value : graph)
		window->draw(value);
}

InsertionSort::~InsertionSort() {}