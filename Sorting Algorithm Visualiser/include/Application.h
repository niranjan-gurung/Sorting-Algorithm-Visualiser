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

	private:
		// appWindow is shared amongst the rest of the sorting algorithm classes:
		std::shared_ptr<sf::RenderWindow> appWindow;
		sf::Event event;
	
		std::unique_ptr<SortInterface> sortAlgorithm;
		u32 sleepTime;
	};
}