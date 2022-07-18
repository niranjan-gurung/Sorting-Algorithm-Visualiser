#include "..\include\MergeSort.h"

MergeSort::MergeSort(std::shared_ptr<sf::RenderWindow> window)
	: SortInterface(window), merged(false) {}

bool MergeSort::Merge(
	std::array<u32, MAX_SIZE>& randomNumberList, 
	std::array<Rect, MAX_SIZE>& graph,
	std::array<u32, MAX_SIZE>& tmp,
	std::array<Rect, MAX_SIZE>& graphtmp,
	int left, 
	int mid, 
	int right)
{
	int i = left;
	int j = mid+1;
	int k = left;

	/* checks if value being copied from tmp list into original list is the exact same:
	 * if value is the same, don't swap cause the value is already at correct place.
	 */
	bool swap;
	
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
		// method returns false if the value being copied is the same as the original:
		if (tmp[p] == randomNumberList[p])
		{
			swap = false;
		}
		else
		{
			swap = true;
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
			//return swap;
		}
	}
	return swap;
}

void MergeSort::Sort(
		std::array<u32, MAX_SIZE>& randomNumberList, 
		std::array<Rect, MAX_SIZE>& graph, 
		int left,
		int right,
		bool& merged)
{
	if (left == right)
		return;

	int mid = (left+right)/2;
	
	Sort(randomNumberList, graph, left, mid, merged);
	if (merged) return;
	
	Sort(randomNumberList, graph, mid+1, right, merged);
	if (merged) return;
	
	if (Merge(randomNumberList, graph, tmp, graphtmp, left, mid, right))
		merged = true;
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
			if (startBtn.getGlobalBounds().contains(
				window->mapPixelToCoords(
					sf::Mouse::getPosition(*window))))
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
		merged = false;
		Sort(randomNumberList, graph, left, right, merged);
		if (std::is_sorted(randomNumberList.begin(), randomNumberList.end()))
		{
			//graph[index].setFillColor(sf::Color::Green);
			isAppRunning = false;
		}
	}
}

void MergeSort::Render()
{
	window->draw(startBtn);
	for (const auto& value : graph)
		window->draw(value);
}

MergeSort::~MergeSort() {}