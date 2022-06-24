#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

// bubble sort algorithm
void BubbleSort(std::vector<uint32_t>& randomNumberList, 
                std::vector<sf::RectangleShape>& graph, 
                const size_t& listSize)
{
    for (size_t i = listSize; i > 0; i--) 
    {
        for (size_t j = listSize-1; j > 0; j--)
        {
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
                sf::sleep(sf::milliseconds(10));
                break;
            }
        }
        sf::sleep(sf::milliseconds(10));
        break;
    }
}

// selection sort
void SelectionSort(std::vector<uint32_t>& randomNumberList, 
                    std::vector<sf::RectangleShape>& graph, 
                    const size_t& listSize)
{
    for (size_t i = 0; i < listSize-1; i++)
    {
        uint32_t minIndex = i;
        for (size_t j = i+1; j < listSize; j++)
        {
            if (randomNumberList[j] < randomNumberList[minIndex])
            {
                minIndex = j;
            }
            sf::sleep(sf::milliseconds(2));
            break;
        }
        // swap from the numbers list:
        std::swap(randomNumberList[minIndex], randomNumberList[i]);
        // swap bar from graph list:
        std::swap(graph[minIndex], graph[i]);

        float xCoord = graph[i].getPosition().x;
        graph[i].setPosition(
            graph[minIndex].getPosition().x, 
            graph[i].getPosition().y
        );
        graph[minIndex].setPosition(
            xCoord, 
            graph[minIndex].getPosition().y
        );
    }
}

// insertion sort
void InsertionSort(std::vector<uint32_t>& randomNumberList,
    std::vector<sf::RectangleShape>& graph,
    const size_t& listSize)
{
    for (int i = 0; i < listSize; i++)
    {
        for (int j = 0; j < listSize; j++)
        {

        }
    }
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Sorting Algorithm Visualiser!");
    window.setVerticalSyncEnabled(true);

    sf::Font font;
    if (!font.loadFromFile("./font/arial.ttf"))
    {
        std::cout << "Couldn't load font.." << std::endl;
    }

    sf::Text startBtn;
    startBtn.setFont(font);
    startBtn.setCharacterSize(20);
    startBtn.setFillColor(sf::Color::Red);
    startBtn.setString("Start!");
    startBtn.setOrigin(startBtn.getGlobalBounds().width/2, startBtn.getGlobalBounds().height/2);
    startBtn.setPosition(100, 50);

    const size_t MAX_SIZE = 80;

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<uint32_t> generate(1, 500);

    // init empty lists:
    std::vector<uint32_t> randomNumberList(MAX_SIZE);
    std::vector<sf::RectangleShape> graph(MAX_SIZE);
    
    int index = 0;                  // index tracker of graph list
    float barGraphSpacing = 10;     // tracks spacing between each individual graph's bars.

    uint32_t windowSizeY = window.getSize().y;

    for_each(randomNumberList.begin(), randomNumberList.end(), 
        [&](uint32_t& randomNumberList) 
    { 
        // generate random numbers for the array list:
        randomNumberList = generate(rng);

        // generate bar height based on the current index of the randomNumberList:
        graph[index] = sf::RectangleShape(sf::Vector2f(10.f, randomNumberList));
        graph[index].setFillColor(sf::Color::Green);
        graph[index].setPosition(
            barGraphSpacing, 
            windowSizeY-graph[index].getGlobalBounds().height
        );
        index++;
        barGraphSpacing += 15;    // +30
    });

    // size alias:
    size_t listSize = randomNumberList.size();

    // print numbers on console:
    for (const auto& value : randomNumberList)
        std::cout << value << std::endl;

    bool started = false;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::MouseButtonPressed:
                if (startBtn.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
                {
                    std::cout << "start button clicked.\n";
                    started = true;
                }
                break;
            }
        }

        if (started)
        {
            // bubble sort:
            //BubbleSort(randomNumberList, graph, listSize);  
            // selection sort:
            SelectionSort(randomNumberList, graph, listSize);  
        }
        if (std::is_sorted(randomNumberList.begin(), randomNumberList.end()))
        {
            started = false;
        }

        window.clear();
        window.draw(startBtn);

        for (const auto& value : graph)
            window.draw(value);

        window.display();
    }
}