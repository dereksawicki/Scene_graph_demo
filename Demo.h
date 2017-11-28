#ifndef DEMO_H
#define DEMO_H


#include "SceneNode.h"
#include "Circle.h"

#include <SFML/Graphics.hpp>
#include <memory>

class Demo {

public:
	Demo();

	void update(sf::Time dt);
	void handleEvents(sf::Event& event);
	void handleInput();
	void render(sf::RenderWindow& window);

private:
	SceneNode mSceneGraph;
	sf::Texture mNodeTexture;

	std::vector<Circle*> mNodes;
	std::vector<Circle*>::iterator mSelected;
};




#endif