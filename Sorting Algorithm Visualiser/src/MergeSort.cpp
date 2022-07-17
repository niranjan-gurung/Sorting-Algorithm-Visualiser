#include "..\include\MergeSort.h"

MergeSort::MergeSort(sf::RenderWindow* window)
	: SortInterface(window) {}

void MergeSort::Sort(
		std::array<uint32_t, MAX_SIZE>& randomNumberList, 
		std::array<sf::RectangleShape, MAX_SIZE>& graph, 
		const int& listSize,
		int left,
		int right)
{
	if (left == right)
		return;
	
	int mid = (left+right)/2;
	Sort(randomNumberList, graph, listSize, left, mid);
	Sort(randomNumberList, graph, listSize, mid+1, right);
	Merge(randomNumberList, graph, listSize, left, mid, right); 
}

void MergeSort::Merge(
	std::array<uint32_t, MAX_SIZE>& randomNumberList, 
	std::array<sf::RectangleShape, MAX_SIZE>& graph, 
	const int& listSize, 
	int left, 
	int mid, 
	int right)
{
	int i = left;
	int j = mid+1;
	int k = left;
	
	std::vector<uint32_t> tmp(listSize);
	std::vector<sf::RectangleShape> graphtmp(listSize);
	
	while (i <= mid && j <= right)
	{
	    if (randomNumberList[i] <= randomNumberList[j])
	    {
	        tmp[k] = randomNumberList[i];
	        graphtmp[k] = graph[i++];
	    }
	    else
	    {
	        tmp[k] = randomNumberList[j];
	        graphtmp[k] = graph[j++];
	    }
	    k++;
	}
	
	while (i <= mid)
	{
	    tmp[k] = randomNumberList[i];
	    graphtmp[k++] = graph[i++];
	}
	
	while (j <= right) 
	{
	    tmp[k] = randomNumberList[j];
	    graphtmp[k++] = graph[j++];
	}
	
	for (int p = left; p <= right; p++)
	{
	    std::swap(tmp[p], randomNumberList[p]);
	    std::swap(graph[p], graphtmp[p]);
	    float xCoord = graph[p].getPosition().x;
	    graph[p].setPosition(
	        graphtmp[p].getPosition().x, 
	        graph[p].getPosition().y
	    );
	    graphtmp[p].setPosition(
	        xCoord, 
	        graphtmp[p].getPosition().y
	    );
	}
}

void MergeSort::Update()
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
		int left = 0;
		int right = listSize-1;
		Sort(randomNumberList, graph, listSize, left, right);
		/*if (std::is_sorted(randomNumberList.begin(), randomNumberList.end()))
		{
			graph[index].setFillColor(sf::Color::Green);
			isAppRunning = false;
		}*/
	}
}

void MergeSort::Render()
{
	window->draw(startBtn);
	for (const auto& value : graph)
		window->draw(value);
}

MergeSort::~MergeSort() {}