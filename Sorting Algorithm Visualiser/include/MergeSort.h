#pragma once

#include "SortInterface.h"

class MergeSort : public SortInterface
{
public:
	MergeSort(std::shared_ptr<sf::RenderWindow> window);
	~MergeSort();

	void Update() override;
	void Render() override;
	void Sort(
		std::array<u32, MAX_SIZE>& randomNumberList, 
		std::array<Rect, MAX_SIZE>& graph, 
		int left, 
		int right) override;

private:
	void Merge(
		std::array<u32, MAX_SIZE>& randomNumberList, 
		std::array<Rect, MAX_SIZE>& graph, 
		int left, 
		int mid, 
		int right);
};