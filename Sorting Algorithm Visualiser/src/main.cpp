#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Sorting Algorithm Visualiser!");
    window.setVerticalSyncEnabled(true);
   
    int counter = 0;

    sf::Font font;
    if (!font.loadFromFile("./font/arial.ttf"))
    {
        std::cout << "Couldn't load font.." << std::endl;
    }

    sf::Text t;
    t.setFont(font);
    t.setCharacterSize(20);
    t.setFillColor(sf::Color::Red);
    t.setString("Counter = " + std::to_string(counter));
    t.setOrigin(t.getGlobalBounds().width/2, t.getGlobalBounds().height/2);
    t.setPosition(800/2, 200);

    const size_t MAX_SIZE = 30;

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
        graph[index] = sf::RectangleShape(sf::Vector2f(20.f, randomNumberList));
        graph[index].setFillColor(sf::Color::Green);
        graph[index].setPosition(
            barGraphSpacing, 
            windowSizeY-graph[index].getGlobalBounds().height
        );
        index++;
        barGraphSpacing += MAX_SIZE;    // +30
    });

    // size alias:
    size_t listSize = randomNumberList.size();

    for (const auto& value : randomNumberList)
        std::cout << value << std::endl;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        //sf::sleep(sf::milliseconds(10));
        t.setString("Counter = " + std::to_string(counter++));

        // bubble sort algorithm
        for (size_t i = 0; i < listSize; i++) 
        {
            /*graph[i].setFillColor(sf::Color::Red);
            graph[i+1].setFillColor(sf::Color::Red);*/
            for (size_t j = 0; j < listSize-1; j++)
            {
                if (randomNumberList[j] > randomNumberList[j+1])
                {
                    // swap from the numbers list:
                    std::swap(randomNumberList[j], randomNumberList[j+1]);

                    // swap bar from graph list:
                    std::swap(graph[j], graph[j+1]);
                    sf::Vector2f temp(
                        graph[j].getPosition().x, 
                        graph[j].getPosition().y
                    );
                    graph[j].setPosition(
                        graph[j+1].getPosition().x, 
                        graph[j].getPosition().y
                    );
                    graph[j+1].setPosition(
                        temp.x, 
                        graph[j+1].getPosition().y
                    );
                }
            }
            sf::sleep(sf::milliseconds(200));
            graph[i].setFillColor(sf::Color::Green);
            graph[i+1].setFillColor(sf::Color::Green);
            break;
        }

        window.clear(sf::Color::White);
        window.draw(t);

        for (const auto& value : graph)
            window.draw(value);

        window.display();
    }
}