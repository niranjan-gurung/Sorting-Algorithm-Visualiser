#include "../include/Application.h"

namespace SortVisualiser {

	// list used for ImGui::Combo dropdown menu:
	static const char* algorithmList[] = { 
		"Bubble Sort", "Insertion Sort", "Selection Sort", "Merge Sort" 
	};

	Application::Application() 
		: sleepTime(20)
	{
		appWindow = std::make_shared<sf::RenderWindow>(
			sf::VideoMode(1280, 720),
			"Sorting Algorithm Visualiser!"
		);
		appWindow->setVerticalSyncEnabled(true);
		
		// init ImGui context:		
		ImGui::SFML::Init(*appWindow);

		// bubble sort by default:
		currentAlgorithm = std::make_unique<BubbleSort>(appWindow);
	}

	void Application::UpdateImGuiWindow() 
	{
		ImGui::Begin("settings");

		// start sorting:
		if (ImGui::Button("start visualisation"))
		{
			if (!settings.isSorted)
			{
				std::cout << "started visualisation.\n";
				settings.isAppRunning = true;
			}
			else
				std::cout << "List already sorted.\n";
		}
		// choose algorithm:
		if (ImGui::Combo("Algorithms", &settings.selected, algorithmList, IM_ARRAYSIZE(algorithmList)))
		{
			switch (settings.selected)
			{
			case 0:
				std::cout << "bubble\n";
				currentAlgorithm = std::make_unique<BubbleSort>(appWindow);
				break;
			case 1:
				std::cout << "insertion\n";
				currentAlgorithm = std::make_unique<InsertionSort>(appWindow);
				break;
			case 2:
				std::cout << "selection\n";
				currentAlgorithm = std::make_unique<SelectionSort>(appWindow);
				break;
			case 3:
				std::cout << "merge\n";
				currentAlgorithm = std::make_unique<MergeSort>(appWindow);
				break;
			}
		}

		// shuffle the current list:
		if (ImGui::Button("shuffle"))
		{
			std::cout << "shuffle button clicked.\n";
			settings.isShuffled = true;
		}

		// inline 'shuffle' and 'generate new list' button.
		ImGui::SameLine();
		
		// generate a completely new list of values: 
		if (ImGui::Button("generate new list"))
		{
			std::cout << "new list created.\n";
			settings.generateNewList = true;
		}
		ImGui::End();
	}

	void Application::Run()
	{
		sf::Clock dt;
		while (appWindow->isOpen())
		{
			Update(dt);
			Render();
		}
	}

	void Application::Update(sf::Clock& dt)
	{
		if (currentAlgorithm != nullptr)
		{
			currentAlgorithm->Update(dt, settings);
			UpdateImGuiWindow();
		}
		else
			appWindow->close();
	}

	void Application::Render()
	{
		appWindow->clear(sf::Color::White);

		// pausing between renders to show sorting animation:
		//sf::sleep(sf::milliseconds(sleepTime));
		if (currentAlgorithm != nullptr)
		{
			currentAlgorithm->Render();
			ImGui::SFML::Render(*appWindow);
		}
	
		appWindow->display();
	}

	Application::~Application() 
	{
		ImGui::SFML::Shutdown();
	}
}