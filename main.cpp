/*

SceneGraph demo
-want to be able to add/remove scene nodes
-move node, move node and children
-rotate children
-tab through nodes


*/

#include "SceneNode.h"
#include "Circle.h"
#include "Demo.h"

#include <SFML/Graphics.hpp>

#include <iostream>
#include <memory>

int main() 
{

	sf::RenderWindow window(sf::VideoMode(640, 480), "SceneGraph Demo", sf::Style::Close);
	
	Demo demo;
		
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const sf::Time TIME_PER_FRAME = sf::seconds(1.f / 60.f);
	while (window.isOpen())
	{

		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;


		while (timeSinceLastUpdate > TIME_PER_FRAME)
		{
			timeSinceLastUpdate -= TIME_PER_FRAME;

			sf::Event event;
			while (window.pollEvent(event)) {
				if (event.type == sf::Event::Closed) {
					window.close();
				}

				demo.handleEvents(event);
			}


			demo.handleInput();


			demo.update(TIME_PER_FRAME);
		}


		// render
		window.clear();

		demo.render(window);

		window.display();

	}

}