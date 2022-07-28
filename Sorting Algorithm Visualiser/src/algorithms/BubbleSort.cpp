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

void BubbleSort::Update(sf::Clock& dt) 
{
	while (window->pollEvent(event))
	{
		ImGui::SFML::ProcessEvent(event);

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

	ImGui::SFML::Update(*window, dt.restart());
	
	ImGui::Begin("settings");

	if (ImGui::Button("start visualisation"))
		std::cout << "started visualisation.\n";
	/*if (ImGui::Combo("Algorithms", &selected, algorithmList, algorithmList.size()))
	{
		switch (selected)
		{
		case 0:
			std::cout << "bubble\n";
			break;
		case 1:
			std::cout << "insertion\n";
			break;
		case 2:
			std::cout << "selection\n";
			break;
		case 3:
			std::cout << "merge\n";
			break;
		}
	}*/

	if (ImGui::Button("generate new list"))
		std::cout << "new list created.\n";
	if (ImGui::Button("shuffle"))
		std::cout << "list shuffled.\n";

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
	ImGui::End();
}

void BubbleSort::Render() 
{
	// draw all UI texts:
	for (const auto& value : UIElements)
		window->draw(value.second);

	for (const auto& value : graph)
		window->draw(value);

	ImGui::SFML::Render(*window);
}

BubbleSort::~BubbleSort() {}