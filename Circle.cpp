#include "Circle.h"



Circle::Circle(sf::Texture& texture)
: mSprite(texture)
, mIsSelected(false)
{
	setType(SceneNode::TYPE::Circle);
}

void Circle::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(mSprite, states);
}

void Circle::setVelocity(sf::Vector2f velocity)
{
	mVelocity = velocity;
}

void Circle::toggleSelection()
{
	mIsSelected = !mIsSelected;
	if (mIsSelected) 
	{
		mSprite.setColor(sf::Color::Green);
	}
	else
	{
		mSprite.setColor(sf::Color::White);
	}
}

void Circle::setVelocity(float vx, float vy)
{
	mVelocity.x = vx;
	mVelocity.y = vy;
}

sf::Vector2f Circle::getVelocity() const
{
	return mVelocity;
}

void Circle::updateCurrent(sf::Time dt)
{
	move(mVelocity*dt.asSeconds());
	mVelocity = sf::Vector2f(0.f, 0.f);
}