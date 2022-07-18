#include "../include/Application.h"

namespace SortVisualiser {

	Application::Application()
	{
		appWindow.create(sf::VideoMode(1280, 720), "Sorting Algorithm Visualiser!");
		appWindow.setVerticalSyncEnabled(true);

		sortAlgorithm = std::make_unique<SelectionSort>(&appWindow);
	}

	void Application::Run()
	{
		while (appWindow.isOpen())
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
			appWindow.close();
	}

	void Application::Render()
	{
		appWindow.clear();

		sf::sleep(sf::milliseconds(30));
		if (sortAlgorithm != nullptr)
			sortAlgorithm->Render();
	
		appWindow.display();
	}

	Application::~Application() {}
}