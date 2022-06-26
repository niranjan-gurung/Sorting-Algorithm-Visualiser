#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

// bubble sort algorithm
void BubbleSort(std::vector<uint32_t>& randomNumberList, 
                std::vector<sf::RectangleShape>& graph, 
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

// selection sort
void SelectionSort(std::vector<uint32_t>& randomNumberList, 
                    std::vector<sf::RectangleShape>& graph, 
                    const int& listSize)
{
    for (int i = listSize-1; i >= 0; i--)
    {
        uint32_t minIndex = i;
        for (int j = i-1; j >= 0; j--)
        {
            if (randomNumberList[j] > randomNumberList[minIndex])
            {
                minIndex = j;
            }
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
        std::cout << "swapped\n";
        //return;
    }
}

// insertion sort
void InsertionSort(std::vector<uint32_t>& randomNumberList,
    std::vector<sf::RectangleShape>& graph,
    const int& listSize)
{
    for (int i = 1; i < listSize; i++)
    {
        graph[i].setFillColor(sf::Color::Red);
        uint32_t key = randomNumberList[i];
        int j = i-1;
        while (j >= 0 && randomNumberList[j] > key)
        {
            // swap from the numbers list:
            std::swap(randomNumberList[j], randomNumberList[j+1]);
            // swap bar from graph list:
            std::swap(graph[j], graph[j+1]);

            float xCoord = graph[j].getPosition().x;
            graph[j].setPosition(
                graph[j+1].getPosition().x, 
                graph[j].getPosition().y
            );
            graph[j+1].setPosition(
                xCoord, 
                graph[j+1].getPosition().y
            );
            graph[i].setFillColor(sf::Color::Green);
            return;
        }
        graph[j].setFillColor(sf::Color::Green);
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

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<uint32_t> generate(1, 500);

    constexpr int MAX_SIZE = 80;

    /* init empty lists: 
     * randomNumberList = number representing a bar
     * graph = bar that visualises the corresponding number from randomNumberList.
     */
    std::vector<uint32_t> randomNumberList(MAX_SIZE);
    std::vector<sf::RectangleShape> graph(MAX_SIZE);
    
    int barHeight = 8;
    int barGraphSpacing = 15;     // tracks spacing between each individual graph's bars.

    uint32_t windowSizeY = window.getSize().y;

    // init list values:
    for (auto& value : randomNumberList)
    {
        value = barHeight;
        barHeight += 8;
    }

    // shuffle list:
    std::shuffle(randomNumberList.begin(), randomNumberList.end(), std::mt19937{ std::random_device{}() });
    
    // assign randomNumberList values to corresponding index from graph list:
    for (int i = 0; i < graph.size(); i++)
    {
        graph[i] = sf::RectangleShape(sf::Vector2f(10.f, randomNumberList[i]));
        graph[i].setFillColor(sf::Color::Green);
        graph[i].setPosition(
            barGraphSpacing, 
            windowSizeY-graph[i].getGlobalBounds().height
        );
        barGraphSpacing += 15;
    }

    // size alias:
    const int listSize = randomNumberList.size();

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

        window.clear();
        window.draw(startBtn);

        if (started)
        {
            // bubble sort:
            BubbleSort(randomNumberList, graph, listSize);  
            // selection sort:
            //SelectionSort(randomNumberList, graph, listSize);  
            // insertion sort:
            //InsertionSort(randomNumberList, graph, listSize);
        }
        if (std::is_sorted(randomNumberList.begin(), randomNumberList.end()))
        {
            started = false;
        }

        sf::sleep(sf::milliseconds(50));
        for (const auto& value : graph)
        {
            window.draw(value);
        }

        window.display();
    }
}