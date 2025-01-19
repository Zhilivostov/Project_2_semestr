#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Window.h"
#include "Body.h"

class Game final
{
private:

	static const int startX = 800;
	static const int startY = 100;

	static const int boundX = 1200; // ширина окна
	static const int boundY = 900; // высота окна
	const float holeX = 600;
	const float holeY = 450;
	const float holeVX = 0.0;
	const float holeVY = 0.0;
	const float holeM = 1000;

public:

	Game() = default;

	const void start()
	{
		sf::Event event;
		sf::RenderWindow window(sf::VideoMode(startX, startY), "If you want play One Star simulator, press on window. Else close window.", sf::Style::Default);
		window.clear(sf::Color::Black);
		window.display();
		while (window.isOpen())
		{
			while (window.pollEvent(event)) //пока окно открыто
			{
				if (event.type == sf::Event::Closed) // закрытие окна
					window.close();

				if (event.type == sf::Event::MouseButtonPressed) // 
				{
					newGame();
				}

			}
		}
	}

	const void newGame()
	{
		Body first_object{ holeX, holeY, holeVX, holeVY, holeM };
		std::vector<Body> bodies = { first_object };

		sf::ContextSettings settings;
		settings.antialiasingLevel = 8; // уровень сглаживания
		sf::RenderWindow window(sf::VideoMode(boundX, boundY), "One Star Simulator", sf::Style::Close, settings);

		int msForFrame = 10;

		Window a;

		while (window.isOpen())
		{
			std::vector<Body> bodiesToAdd = a.handleEvents(window);

			window.clear(sf::Color::Black);

			a.update(window, bodies);
			bodies.insert(bodies.end(), bodiesToAdd.begin(), bodiesToAdd.end());
			bodiesToAdd.clear();

			window.display();

			a.sleep(msForFrame);
		}
	}
	
	~Game() = default;
};