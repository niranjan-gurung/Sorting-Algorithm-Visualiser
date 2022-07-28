//#include "../include/Application.h"

#include <iostream>

#include "../imgui/imgui.h"
#include "../imgui/imgui-SFML.h"
#include "../include/SFML/Graphics.hpp"

int main()
{
    //SortVisualiser::Application app;
    //app.Run();

    sf::RenderWindow window(sf::VideoMode(800, 800), "imgui-sfml-app");
    ImGui::SFML::Init(window);

    sf::CircleShape c(200.f, 100.f);
    c.setFillColor(sf::Color(204, 77, 5));
    c.setPosition(200, 200);

    const char* a[] = { "Bubble Sort", "Insertion Sort", "Selection Sort", "Merge Sort" };
    int selected = 0;

    sf::Clock deltaClock;
    while (window.isOpen())
    {
        sf::Event ev;
        while (window.pollEvent(ev))
        {
            ImGui::SFML::ProcessEvent(ev);
            if (ev.type == sf::Event::Closed)
                window.close();
        }

        ImGui::SFML::Update(window, deltaClock.restart());

        ImGui::Begin("settings");
        if (ImGui::Combo("Algorithms", &selected, a, IM_ARRAYSIZE(a)))
        {
            switch (selected)
            {
            case 0:
                std::cout << "bubble\n";
                break;
            case 1:
                std::cout << "insertion\n";
                break;
            case 2:
                std::cout << "selection\n";
                break;
            case 3:
                std::cout << "merge\n";
                break;
            }
        }
        if (ImGui::Button("generate new list"))
            std::cout << "new list created.\n";
        if (ImGui::Button("shuffle"))
            std::cout << "list shuffled.\n";
        ImGui::End();

        window.clear(sf::Color(18, 33, 43));
        window.draw(c);
        ImGui::SFML::Render(window);
        window.display();
    }
    ImGui::SFML::Shutdown();
} 