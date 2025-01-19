#pragma once
#include "Body.h"
#include <set>
#include <chrono>
#include <thread>
#include <SFML/Graphics.hpp>

using namespace bd;
//class MyCircleShape
//{
////private:
//
//public:
//
//	MyCircleShape() = default;
//
//	virtual sf::CircleShape set_param_shape() = 0;
//	virtual ~MyCircleShape() = default;
//
//};

class Window final
{
public:

	Window() = default;
	
	std::vector<Body> handleEvents(sf::RenderWindow& window) {
		std::vector<Body> newBodies;
		sf::Event event;

		while (window.pollEvent(event)) //пока окно открыто
		{
			if (event.type == sf::Event::Closed) // закрытие окна
				window.close();
			if (event.type == sf::Event::MouseButtonPressed) // 
			{
				sf::Vector2i position = sf::Mouse::getPosition(window);
				if (event.mouseButton.button == sf::Mouse::Left) // 
				{
					newBodies.push_back(Body{ static_cast<float>(position.x), static_cast<float>(position.y), 0.0, 0.0, 100.0 });
				}
				else
				{
					newBodies.push_back(Body{ static_cast<float>(position.x), static_cast<float>(position.y), 0.0, 0.0, 1000.0 });
				}
			}
		}

		return newBodies;
	}

	sf::CircleShape renderBody(Body& b)
	{
		if (b.m >= sunMass * 4)
		{
			b.r = b.m * radiusCoef * radiusCoef;
		}
		else
		{
			b.r = b.m * radiusCoef;
		}
		
		sf::CircleShape circle(b.r);
		circle.setOrigin(b.r, b.r);
		circle.setPosition(b.x, b.y);
		if (b.m >= sunMass * 4)
		{
			circle.setFillColor(sf::Color::Magenta);
		}
		else if (b.m >= sunMass)
		{
			circle.setFillColor(sf::Color::Yellow);
		}
		else
		{
			circle.setFillColor(sf::Color::Blue);
		}
		
		return circle;
	}

	void update(sf::RenderWindow& window, std::vector<Body>& bodies)
	{
		std::set<int> deleteBodies;
		int size = bodies.size();

		for (int i = 0; i < size; i++)
		{
			Body& p0 = bodies[i];
			for (int j = 0; j < size; j++)
			{
				if (i == j)
					continue;
				Body& p = bodies[j];
				double d = sqrt(pow(p0.x - p.x, 2) + pow(p0.y - p.y, 2)); //дистанция между телами

				if (d > p0.r + p.r)
				{
					p0.vx += coef * p.m / d / d * (p.x - p0.x) / d;
					p0.vy += coef * p.m / d / d * (p.y - p0.y) / d;
				}
				else
				{
					if (p0.m >= sunMass && p.m >= sunMass)
					{
						p.m += p0.m * 0.5;
						deleteBodies.insert(i);
					}
					else
					{
						if (p0.m < sunMass)
						{
							deleteBodies.insert(i);
						}
						else
						{
							p0.m += p.m;
						}

						if (p.m < sunMass)
						{
							deleteBodies.insert(j);
						}
						else
						{
							p.m += p0.m;
						}
					}
				}
			}
			p0.x += p0.vx;
			p0.y += p0.vy;

			Window a;
			sf::CircleShape circle = a.renderBody(p0);
			window.draw(circle);
		}

		std::vector<Body> copy_bodies;

		for (int i = 0; i < bodies.size(); ++i)
		{
			if (deleteBodies.find(i) == deleteBodies.end())
			{
				copy_bodies.push_back(bodies[i]);
			}
		}

		bodies = copy_bodies;
	}

	void sleep(int ms)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(ms));
	}

	~Window() = default;
};