#include <SFML/Graphics.hpp>
#include <iostream>
#include <array>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Sorting Algorithm Visualiser!");
    window.setVerticalSyncEnabled(true);
    
    int counter = 0;

    sf::Font font;
    if (!font.loadFromFile("./font/arial.ttf"))
        std::cout << "Couldn't load font.." << std::endl;

    sf::Text t;
    t.setFont(font);
    t.setCharacterSize(20);
    t.setFillColor(sf::Color::Red);
    t.setString("Counter = " + std::to_string(counter));
    t.setOrigin(t.getGlobalBounds().width/2, t.getGlobalBounds().height/2);
    t.setPosition(800/2, 600/2);

    std::array<int, 10> a = { 5, 7, 10, 2, 37, 21, 1, 58, 44, 2 };

    // bubble sort algorithm
    for (size_t i = 0; i < 10; i++) 
    {
        for (size_t j = 0; j < 10 - 1; j++)
        {
            if (a[j] > a[j + 1])
            {
                int temp = a[j];
                a[j] = a[j+1];
                a[j+1] = temp;
            }
        }
    }

    for (const auto& v : a)
        std::cout << v << std::endl;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::sleep(sf::milliseconds(100));
        t.setString("Counter = " + std::to_string(counter++));

        window.clear(sf::Color::White);
        window.draw(t);
        window.display();
    }
}