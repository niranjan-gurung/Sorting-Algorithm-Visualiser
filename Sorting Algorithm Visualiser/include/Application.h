#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Application
{
public:
	Application();
	~Application();

	void Start();
	void Update();
	void Render();

private:
	void InitAppWindow();
};