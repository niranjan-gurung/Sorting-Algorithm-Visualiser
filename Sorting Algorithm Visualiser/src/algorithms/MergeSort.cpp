#include "../../include/MergeSort.h"

MergeSort::MergeSort(std::shared_ptr<sf::RenderWindow> window)
	: SortInterface(window), merged(false) {}

/* Merge sub-arrays of current recursion:
 * @params randomNumberList/graph: main list that will be drawn on the screen.
 * @params ncopy/gcopy: 
	- sub-array that holds sorted variations for the current merge call iteration.
	- used to compare and fill tmp array with sorted values of current sub-array.
 */
bool MergeSort::Merge(
	std::array<u32, MAX_SIZE>& randomNumberList, 
	std::array<Rect, MAX_SIZE>& graph,
	std::array<u32, MAX_SIZE>& copyList,
	std::array<Rect, MAX_SIZE>& copyGraph,
	int left, 
	int mid, 
	int right)
{
	int i = left;
	int j = mid+1;
	int k = left;

	// temporary lists to hold sorted values before moving them back into original array:
	std::vector<u32> tmp(right+1);
	std::vector<Rect> graphtmp(right+1);

	// sort values from the current sub-array(copyList) and fill tmp with it:
	while (i <= mid && j <= right)
	{
		if (copyList[i] < copyList[j])
		{
			tmp[k] = copyList[i];
			graphtmp[k] = copyGraph[i];
			i++;
		}
		else
		{
			tmp[k] = copyList[j];
			graphtmp[k] = copyGraph[j];
			j++;
		}
		k++;
	}

	while (i <= mid)
	{
		tmp[k] = copyList[i];
		graphtmp[k] = copyGraph[i];
		i++, k++;
	}

	while (j <= right) 
	{
		tmp[k] = copyList[j];
		graphtmp[k] = copyGraph[j];
		j++, k++;
	}

	// move sorted order values from tmp back into ncopy list.
	// this sets up copyList for next merge call:
	for (int p = left; p <= right; p++)
	{
		copyList[p] = tmp[p];
		copyGraph[p] = graphtmp[p];
	}

	/* checks if value being copied from tmp list into original list is the exact same:
	* if value is the same, don't swap cause the value is already at correct place.
	*/
	bool swap;

	for (int p = left; p <= right; p++)
	{
		graph[p].setFillColor(bar);
		// method returns false if the value being copied is the same as the original:
		if (tmp[p] == randomNumberList[p])
			swap = false;
		else
		{
			std::swap(randomNumberList[p], tmp[p]);
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
			graph[p].setFillColor(barSwapping);
			index = p;
			swap = true;
			return swap;
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
	if (Merge(randomNumberList, graph, copyList, copyGraph, left, mid, right))
		merged = true;
}

void MergeSort::Update(sf::Clock& dt)
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
	break;
	case 1:
	std::cout << "insertion\n";
	sortAlgorithm = std::make_unique<InsertionSort>(window);
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

	// shuffle list:
	if (ImGui::Button("shuffle"))
	{
		std::cout << "shuffle button clicked.\n";
		ShuffleList();
		std::copy(
			std::begin(randomNumberList),
			std::end(randomNumberList),
			std::begin(copyList)
		);
		std::copy(
			std::begin(graph),
			std::end(graph),
			std::begin(copyGraph)
		);
		shuffled = true;
		sorted = false;
	}

	if (isAppRunning && shuffled)
	{
		int left = 0;
		int right = MAX_SIZE-1;
		merged = false;
		Sort(randomNumberList, graph, left, right, merged);
		
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

void MergeSort::Render()
{
	for (const auto& value : graph)
		window->draw(value);
	ImGui::SFML::Render(*window);
}

MergeSort::~MergeSort() {}