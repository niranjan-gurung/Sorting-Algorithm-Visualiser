#pragma once

#include "SortInterface.h"

class InsertionSort : public SortInterface
{
public:
	InsertionSort(std::shared_ptr<sf::RenderWindow> window);
	~InsertionSort();

	void Update(sf::Clock& dt, util::Settings& settings) override;
	void Render() override;
	void Sort(
		std::array<u32, MAX_SIZE>& randomNumberList, 
		std::array<Rect, MAX_SIZE>& graph) override;
};