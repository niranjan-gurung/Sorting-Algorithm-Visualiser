#pragma once

#include "SortInterface.h"

class BubbleSort : public SortInterface
{
public:
	BubbleSort(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<SortInterface> algorithm);
	~BubbleSort();

	void Update(sf::Clock& dt) override;
	void Render() override;
	void Sort(
		std::array<u32, MAX_SIZE>& randomNumberList, 
		std::array<Rect, MAX_SIZE>& graph) override;
};