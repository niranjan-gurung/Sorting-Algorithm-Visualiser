#include "../include/SelectionSort.h"

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
		graph[minIndex].setFillColor(sf::Color::Red);
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
	    graph[minIndex].setFillColor(sf::Color::Green);
	    
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
			if (startBtn.getGlobalBounds().contains(window->mapPixelToCoords(sf::Mouse::getPosition(*window))))
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

void SelectionSort::Render()
{
	window->draw(startBtn);
	for (const auto& value : graph)
		window->draw(value);
}

SelectionSort::~SelectionSort() {}