#include "..\include\MergeSort.h"

MergeSort::MergeSort(std::shared_ptr<sf::RenderWindow> window)
	: SortInterface(window) {}

void MergeSort::Sort(
		std::array<u32, MAX_SIZE>& randomNumberList, 
		std::array<Rect, MAX_SIZE>& graph, 
		int left,
		int right)
{
	if (left == right)
		return;
	
	int mid = (left+right)/2;
	Sort(randomNumberList, graph, left, mid);
	Sort(randomNumberList, graph, mid+1, right);
	Merge(randomNumberList, graph, left, mid, right); 
}

void MergeSort::Merge(
	std::array<u32, MAX_SIZE>& randomNumberList, 
	std::array<Rect, MAX_SIZE>& graph, 
	int left, 
	int mid, 
	int right)
{
	int i = left;
	int j = mid+1;
	int k = left;

	// temporary lists to hold sorted values before moving them back into original array:
	std::vector<u32> tmp(MAX_SIZE);
	std::vector<Rect> graphtmp(MAX_SIZE);
	
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
		int right = MAX_SIZE-1;
		Sort(randomNumberList, graph, left, right);
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