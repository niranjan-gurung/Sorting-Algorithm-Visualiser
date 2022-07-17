#pragma once

#include "SortInterface.h"

class MergeSort : public SortInterface
{
public:
	MergeSort(sf::RenderWindow* window);
	~MergeSort();

	void Update() override;
	void Render() override;
	void Sort(
		std::array<uint32_t, MAX_SIZE>& randomNumberList, 
		std::array<sf::RectangleShape, MAX_SIZE>& graph, 
		const int& listSize, 
		int left, 
		int right) override;

private:
	void Merge(
		std::array<uint32_t, MAX_SIZE>& randomNumberList, 
		std::array<sf::RectangleShape, MAX_SIZE>& graph, 
		const int& listSize, 
		int left, 
		int mid, 
		int right);
};