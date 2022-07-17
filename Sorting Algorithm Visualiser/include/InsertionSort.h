#pragma once

#include "SortInterface.h"

class InsertionSort : public SortInterface
{
public:
	InsertionSort(sf::RenderWindow* window);
	~InsertionSort();

	void Sort(std::array<uint32_t, MAX_SIZE>& randomNumberList, 
			std::array<sf::RectangleShape, MAX_SIZE>& graph, 
			const int& listSize);

	void Update() override;
	void Render() override;
};