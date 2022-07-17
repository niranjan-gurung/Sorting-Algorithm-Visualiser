#pragma once

#include "SortInterface.h"

class BubbleSort : public SortInterface
{
public:
	BubbleSort(sf::RenderWindow* window);
	~BubbleSort();

	void Sort(std::array<uint32_t, MAX_SIZE>& randomNumberList, 
			std::array<sf::RectangleShape, MAX_SIZE>& graph, 
			const int& listSize);

	void Update() override;
	void Render() override;
};