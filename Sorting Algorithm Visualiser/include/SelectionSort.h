#pragma once

#include "SortInterface.h"

class SelectionSort : public SortInterface
{
public:
	SelectionSort(sf::RenderWindow* window);
	~SelectionSort();

	void Sort(std::array<uint32_t, MAX_SIZE>& randomNumberList, 
		std::array<sf::RectangleShape, MAX_SIZE>& graph, 
		const int& listSize);

	void Update() override;
	void Render() override;
};