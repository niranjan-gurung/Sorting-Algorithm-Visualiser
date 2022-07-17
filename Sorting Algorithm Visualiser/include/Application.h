#pragma once
#include <iostream>
#include <memory>

#include "SortInterface.h"
#include "BubbleSort.h"

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