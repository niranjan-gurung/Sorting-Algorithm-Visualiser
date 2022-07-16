#include "../include/Application.h"

std::random_device dev;
std::mt19937 rng(dev());
std::uniform_int_distribution<uint32_t> generate(1, 500);

Application::Application()
{
	std::cout << "application constructor called!\n";
	
	appWindow.create(sf::VideoMode(1280, 720), "Sorting Algorithm Visualiser!");
	appWindow.setVerticalSyncEnabled(true);

	if (!font.loadFromFile("./font/arial.ttf"))
	{
		std::cout << "Couldn't load font.." << std::endl;
	}

	startBtn.setFont(font);
	startBtn.setCharacterSize(20);
	startBtn.setFillColor(sf::Color::Red);
	startBtn.setString("Start!");
	startBtn.setOrigin(startBtn.getGlobalBounds().width/2, startBtn.getGlobalBounds().height/2);
	startBtn.setPosition(100, 50);

	// init list values:
	for (auto& value : randomNumberList)
	{
		value = barHeight;
		barHeight += 8;
	}

	// shuffle list:
	std::shuffle(randomNumberList.begin(), randomNumberList.end(), std::mt19937{ std::random_device{}() });

	uint32_t windowSizeY = appWindow.getSize().y;

	// assign randomNumberList values to corresponding index from graph list:
	for (int i = 0; i < randomNumberList.size(); i++)
	{
		graph[i] = sf::RectangleShape(sf::Vector2f(10.f, randomNumberList[i]));
		graph[i].setFillColor(sf::Color::Green);
		graph[i].setPosition(
			barGraphSpacing, 
			windowSizeY-graph[i].getGlobalBounds().height
		);
		barGraphSpacing += 15;
	}
}

Application::~Application() {}

// bubble sort algorithm
void Application::BubbleSort(std::array<uint32_t, MAX_SIZE>& randomNumberList, 
	std::array<sf::RectangleShape, MAX_SIZE>& graph, 
	const int& listSize)
{
	for (int i = listSize-1; i > 0; i--) 
	{
		for (int j = listSize-1; j > 0; j--)
		{
			graph[j].setFillColor(sf::Color::Green);
			if (randomNumberList[j] < randomNumberList[j-1])
			{
				// swap from the numbers list:
				std::swap(randomNumberList[j], randomNumberList[j-1]);
				// swap bar from graph list:
				std::swap(graph[j], graph[j-1]);

				float xCoord = graph[j].getPosition().x;
				graph[j].setPosition(
					graph[j-1].getPosition().x, 
					graph[j].getPosition().y
				);
				graph[j-1].setPosition(
					xCoord, 
					graph[j-1].getPosition().y
				);
				graph[j].setFillColor(sf::Color::Red);
				return;
			}
		}
		graph[i].setFillColor(sf::Color::Green);
	}
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
	while (appWindow.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			appWindow.close();
			break;

		case sf::Event::MouseButtonPressed:
			if (startBtn.getGlobalBounds().contains(appWindow.mapPixelToCoords(sf::Mouse::getPosition(appWindow))))
			{
				std::cout << "start button clicked.\n";
				started = true;
			}
			break;
		}
	}
}

void Application::Render()
{
	appWindow.clear();

	appWindow.draw(startBtn);
	
	if (started)
	{
	    // bubble sort:
	    BubbleSort(randomNumberList, graph, listSize);  
	        
	    // selection sort:
	    //SelectionSort(randomNumberList, graph, listSize);  
	        
	    // insertion sort:
	    //InsertionSort(randomNumberList, graph, listSize);
	        
	    // merge sort:
	    //int left = 0;
	    //int right = listSize-1;
	    ////int recursionCounter = 0;
	    //MergeSort(randomNumberList, graph, listSize, left, right);
	}
	if (std::is_sorted(randomNumberList.begin(), randomNumberList.end()))
	{
	    started = false;
	}

	sf::sleep(sf::milliseconds(20));
	for (const auto& value : graph)
	{
		appWindow.draw(value);
	}
	
	appWindow.display();
}