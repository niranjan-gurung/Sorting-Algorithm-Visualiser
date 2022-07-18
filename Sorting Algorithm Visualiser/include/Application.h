#pragma once
#include <memory>

#include "BubbleSort.h"
#include "InsertionSort.h"
#include "SelectionSort.h"
#include "MergeSort.h"

namespace SortVisualiser {

	class Application
	{
	public:
		Application();
		~Application();

		void Run();
		void Update();
		void Render();

	private:
		sf::RenderWindow appWindow;
		sf::Event event;
	
		std::unique_ptr<SortInterface> sortAlgorithm;
	};
}