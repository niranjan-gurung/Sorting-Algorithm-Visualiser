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

		// bubble sort by default:
		currentAlgorithm = std::make_shared<BubbleSort>(appWindow, currentAlgorithm);
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
			currentAlgorithm->Update(dt);
		else
			appWindow->close();
	}

	void Application::Render()
	{
		appWindow->clear(sf::Color::White);

		// pausing between renders to show sorting animation:
		sf::sleep(sf::milliseconds(sleepTime));
		if (currentAlgorithm != nullptr)
			currentAlgorithm->Render();
	
		appWindow->display();
	}

	Application::~Application() 
	{
		ImGui::SFML::Shutdown();
	}
}