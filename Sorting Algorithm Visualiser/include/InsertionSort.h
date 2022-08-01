#pragma once

#include "SortInterface.h"

class InsertionSort : public SortInterface
{
public:
	InsertionSort(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<SortInterface> algorithm);
	~InsertionSort();

	void Update(sf::Clock& dt) override;
	void Render() override;
	void Sort(
		std::array<u32, MAX_SIZE>& randomNumberList, 
		std::array<Rect, MAX_SIZE>& graph) override;
};