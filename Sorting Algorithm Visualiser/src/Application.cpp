#include "../include/Application.h"

Application::Application()
{
	appWindow.create(sf::VideoMode(1280, 720), "Sorting Algorithm Visualiser!");
	appWindow.setVerticalSyncEnabled(true);

	sortAlgorithm = std::make_unique<MergeSort>(&appWindow);
}

Application::~Application() {}

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

	//if (started)
	//{
	//    // merge sort:
	//    //int left = 0;
	//    //int right = listSize-1;
	//    ////int recursionCounter = 0;
	//    //MergeSort(randomNumberList, graph, listSize, left, right);
	//}

	sf::sleep(sf::milliseconds(30));
	if (sortAlgorithm != nullptr)
		sortAlgorithm->Render();
	
	appWindow.display();
}