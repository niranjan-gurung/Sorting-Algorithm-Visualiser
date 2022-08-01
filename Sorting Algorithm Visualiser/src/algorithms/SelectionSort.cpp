#include "../../include/SelectionSort.h"

SelectionSort::SelectionSort(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<SortInterface> algorithm) 
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

void SelectionSort::Update(sf::Clock& dt)
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

	ImGui::Begin("settings");
	// start sorting:
	if (ImGui::Button("start visualisation"))
	{
		if (!sorted)
		{
			std::cout << "started visualisation.\n";
			isAppRunning = true;
		}
		else
			std::cout << "List already sorted.\n";
	}

	/*if (ImGui::Combo("Algorithms", &selected, algorithmList, IM_ARRAYSIZE(algorithmList)))
	{
		switch (selected)
		{
		case 0:
			std::cout << "bubble\n";
			a(selected);
			break;
		case 1:
			std::cout << "insertion\n";
			a(selected);
			break;
		case 2:
			std::cout << "selection\n";
			a(selected);
			break;
		case 3:
			std::cout << "merge\n";
			a(selected);
			break;
		}
	}*/

	if (ImGui::Button("generate new list"))
		std::cout << "new list created.\n";

	// shuffle list:
	if (ImGui::Button("shuffle"))
	{
		std::cout << "shuffle button clicked.\n";
		ShuffleList();
		shuffled = true;
		sorted = false;
	}

	if (isAppRunning && shuffled)
	{
		Sort(randomNumberList, graph);

		// enter once list is fully sorted:
		if (std::is_sorted(randomNumberList.begin(), randomNumberList.end()))
		{
			graph[index].setFillColor(bar);
			sorted = true;
			shuffled = false;
			isAppRunning = false;
		}
	}
	ImGui::End();
}

void SelectionSort::Render()
{
	for (const auto& value : graph)
		window->draw(value);
	ImGui::SFML::Render(*window);
}

SelectionSort::~SelectionSort() {}