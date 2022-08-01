#include "../../include/InsertionSort.h"
#include "../../include/BubbleSort.h"
#include "../../include/SelectionSort.h"
#include "../../include/MergeSort.h"

InsertionSort::InsertionSort(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<SortInterface> algorithm)
	: SortInterface(window) 
{
	currentAlgorithm = algorithm;
}

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

void InsertionSort::Update(sf::Clock& dt)
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

	if (ImGui::Combo("Algorithms", &selected, algorithmList, IM_ARRAYSIZE(algorithmList)))
	{
		switch (selected)
		{
		case 0:
			std::cout << "bubble\n";
			currentAlgorithm = std::make_unique<BubbleSort>(window, currentAlgorithm);
			break;
		case 1:
			std::cout << "insertion\n";
			currentAlgorithm = std::make_unique<InsertionSort>(window, currentAlgorithm);
			break;
		case 2:
			std::cout << "selection\n";
			currentAlgorithm = std::make_unique<SelectionSort>(window, currentAlgorithm);
			break;
		case 3:
			std::cout << "merge\n";
			currentAlgorithm = std::make_unique<MergeSort>(window, currentAlgorithm);
			break;
		}
	}

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

void InsertionSort::Render()
{
	for (const auto& value : graph)
		window->draw(value);
	ImGui::SFML::Render(*window);
}

InsertionSort::~InsertionSort() {}