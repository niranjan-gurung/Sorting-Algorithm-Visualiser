#include "../include/Application.h"

namespace SortVisualiser {
	
	Application::Application() 
		: sleepTime(30)
	{
		appWindow = std::make_shared<sf::RenderWindow>(
			sf::VideoMode(1280, 720),
			"Sorting Algorithm Visualiser!"
		);
		appWindow->setVerticalSyncEnabled(true);

		sortAlgorithm = std::make_unique<InsertionSort>(appWindow);
	}

	void Application::Run()
	{
		while (appWindow->isOpen())
		{
			Update();
			Render();
		}
	}

	void Application::Update()
	{
		if (sortAlgorithm != nullptr)
			sortAlgorithm->Update();
		else
			appWindow->close();
	}

	void Application::Render()
	{
		appWindow->clear();

		// pausing between renders to show sorting animation:
		sf::sleep(sf::milliseconds(sleepTime));
		if (sortAlgorithm != nullptr)
			sortAlgorithm->Render();
	
		appWindow->display();
	}

	Application::~Application() {}
}