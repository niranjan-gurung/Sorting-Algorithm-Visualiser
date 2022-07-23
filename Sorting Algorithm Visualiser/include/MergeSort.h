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
		int right,
		bool& merged) override;

private:
	bool Merge(
		std::array<u32, MAX_SIZE>& randomNumberList, 
		std::array<Rect, MAX_SIZE>& graph, 
		const std::array<u32, MAX_SIZE>& ncopy,
		const std::array<Rect, MAX_SIZE>& gcopy,
		int left, 
		int mid, 
		int right);

private:
	bool merged;

	// temporary lists to hold sorted values before moving them back into original array:
	std::array<u32, MAX_SIZE> numListCopy;
	std::array<Rect, MAX_SIZE> graphListCopy;
};