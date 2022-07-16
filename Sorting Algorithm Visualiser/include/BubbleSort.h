#pragma once

#include "SortInterface.h"

class BubbleSort : public SortInterface
{
public:
	BubbleSort();
	~BubbleSort();

	/*void BubbleSort(std::array<uint32_t, MAX_SIZE>& randomNumberList, 
		std::array<sf::RectangleShape, MAX_SIZE>& graph, 
		const int& listSize);*/

	virtual void Update();
	virtual void Render();
};