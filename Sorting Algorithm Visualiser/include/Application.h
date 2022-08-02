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
 * - Handles ImGui window
 * - Handles Update and Render methods of sorting algorithms
 * - Controls which algorithm is selected
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

		// imgui UI panel:
		void UpdateImGuiWindow();

	private:
		// appWindow is shared amongst the rest of the sorting algorithm classes:
		std::shared_ptr<sf::RenderWindow> appWindow;
		
		// tracks current selected algorithm:
		std::unique_ptr<SortInterface> currentAlgorithm;
		
		// holds boolean flags to control the application flow:
		util::Settings settings;
		
		// delay between frames:
		u32 sleepTime;
	};
}