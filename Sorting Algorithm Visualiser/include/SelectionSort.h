#pragma once

#include "SortInterface.h"

class SelectionSort : public SortInterface
{
public:
	SelectionSort(std::shared_ptr<sf::RenderWindow> window);
	~SelectionSort();

	void Update() override;
	void Render() override;
	void Sort(
		std::array<u32, MAX_SIZE>& randomNumberList, 
		std::array<Rect, MAX_SIZE>& graph) override;
};