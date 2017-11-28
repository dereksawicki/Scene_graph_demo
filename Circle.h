#ifndef CIRCLE_H
#define CIRCLE_H

#include "SceneNode.h"

#include <SFML/Graphics.hpp>

class Circle : public SceneNode
{
public:
	Circle(sf::Texture& texture);

	void setVelocity(sf::Vector2f velocity);
	void setVelocity(float vx, float vy);
	sf::Vector2f getVelocity() const;

	void toggleSelection();

private:
	virtual void updateCurrent(sf::Time dt);
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates state) const;

private:
	bool mIsSelected;

	sf::Sprite mSprite;
	sf::Vector2f mVelocity;
};


#endif