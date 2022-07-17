#include "../include/Application.h"

Application::Application()
{
	appWindow.create(sf::VideoMode(1280, 720), "Sorting Algorithm Visualiser!");
	appWindow.setVerticalSyncEnabled(true);

	sortAlgorithm = std::make_unique<BubbleSort>(&appWindow);
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
	{
		sortAlgorithm->Update();
	}
	else
	{
		appWindow.close();
	}
}

void Application::Render()
{
	appWindow.clear();

	//if (started)
	//{
	//    // bubble sort:
	//    //BubbleSort(randomNumberList, graph, listSize);  
	//        
	//    // selection sort:
	//    //SelectionSort(randomNumberList, graph, listSize);  
	//        
	//    // insertion sort:
	//    //InsertionSort(randomNumberList, graph, listSize);
	//        
	//    // merge sort:
	//    //int left = 0;
	//    //int right = listSize-1;
	//    ////int recursionCounter = 0;
	//    //MergeSort(randomNumberList, graph, listSize, left, right);
	//}
	//if (std::is_sorted(randomNumberList.begin(), randomNumberList.end()))
	//{
	//    started = false;
	//}

	sf::sleep(sf::milliseconds(20));
	if (sortAlgorithm != nullptr)
	{
		sortAlgorithm->Render();
	}
	
	appWindow.display();
}