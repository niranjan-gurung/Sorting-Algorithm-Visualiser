#include "../include/Application.h"

namespace SortVisualiser {
	
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

		// bubble sort by default
		sortAlgorithm = std::make_unique<BubbleSort>(appWindow);
	}

	void Application::Run()
	{
		while (appWindow->isOpen())
		{
			sf::Clock dt;
			Update(dt);
			Render();
		}
	}

	void Application::Update(sf::Clock& dt)
	{
		if (sortAlgorithm != nullptr)
			sortAlgorithm->Update(dt);
		else
			appWindow->close();
	}

	void Application::Render()
	{
		appWindow->clear(sf::Color::White);

		// pausing between renders to show sorting animation:
		sf::sleep(sf::milliseconds(sleepTime));
		if (sortAlgorithm != nullptr)
			sortAlgorithm->Render();
	
		appWindow->display();
	}

	Application::~Application() 
	{
		ImGui::SFML::Shutdown();
	}
}