#pragma once
#include <memory>

#include "BubbleSort.h"
#include "InsertionSort.h"
#include "SelectionSort.h"
#include "MergeSort.h"

/* Main Application:
 * 
 * - Init window
 * - BubbleSort by default
 * - Handles Update and Render methods of sorting algorithms
 * - Controls the amount of time slept in between renders 
 */
namespace SortVisualiser {
	
	class Application
	{
	public:
		Application();
		~Application();

		void Run();
		void Update(sf::Clock& dt);
		void Render();

		//void SelectAlgorithm(int& selected);

	private:
		// appWindow is shared amongst the rest of the sorting algorithm classes:
		std::shared_ptr<sf::RenderWindow> appWindow;
		std::shared_ptr<SortInterface> currentAlgorithm;
		u32 sleepTime;
	};
}