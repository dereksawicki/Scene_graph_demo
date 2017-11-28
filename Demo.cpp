#include "Demo.h"

#include <queue>

Demo::Demo()
{
	mNodeTexture;
	mNodeTexture.loadFromFile("Media/Textures/node.png");


}

void Demo::update(sf::Time dt)
{
	mSceneGraph.update(dt);
}

void Demo::handleEvents(sf::Event& event)
{
	switch (event.type)
	{
	case sf::Event::KeyPressed:
		if (event.key.code == sf::Keyboard::J)
		{
			// create and add child
			std::unique_ptr<Circle> next(new Circle(mNodeTexture));

			if (mNodes.empty())
			{
				next->setPosition(200.f, 200.f);
				next->toggleSelection();

				mNodes.push_back(next.get());

				mSelected = mNodes.begin();
				mSceneGraph.attachChild(std::move(next));
			}
			else
			{
				if (mSelected == mNodes.end())
					return;


				Circle* cur = *mSelected;
				next->setPosition((*mSelected)->getPosition() + sf::Vector2f(3.f, 0.f));
				mNodes.push_back(next.get());

				cur->attachChild(std::move(next));
				cur->toggleSelection();



				mSelected = mNodes.begin();
				(*mSelected)->toggleSelection();
			}
		}
		else if (event.key.code == sf::Keyboard::K)
		{
			if (mSelected == mNodes.end())
				return;

			(*mSelected)->toggleSelection();
			(*mSelected)->kill();

			// restock mNodes
			mNodes.clear();

			std::queue<SceneNode*> bfsQueue;
			bfsQueue.push(&mSceneGraph);
			while (!bfsQueue.empty())
			{
				SceneNode* cur = bfsQueue.front();
				bfsQueue.pop();

				if (cur->getType() == SceneNode::TYPE::Circle)
					mNodes.push_back( dynamic_cast<Circle*>(cur));

				std::vector<SceneNode*> cur_children;
				cur->getChildren(cur_children);
				for (SceneNode* sn : cur_children)
				{
					bfsQueue.push(sn);
				}
			}

			mSelected = mNodes.end();

		}
		else if (event.key.code == sf::Keyboard::Tab)
		{
			// cycle through nodes
			if (mNodes.empty())
				return;
			if (mSelected == mNodes.end())
			{
				mSelected = mNodes.begin();
				(*mSelected)->toggleSelection();
				return;
			}

			(*mSelected)->toggleSelection();
			mSelected++;
			if (mSelected == mNodes.end())
			{
				mSelected = mNodes.begin();
			}
			(*mSelected)->toggleSelection();
		}
	}
}

void Demo::handleInput()
{
	// get and process controller input
	if (!mNodes.empty())
	{
		if (mSelected == mNodes.end())
			return;

		const float speed = 60.f;
		// Translation
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			(*mSelected)->setVelocity(sf::Vector2f(0.f, speed));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			(*mSelected)->setVelocity(sf::Vector2f(speed, 0.f));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			(*mSelected)->setVelocity(sf::Vector2f(-speed, 0.f));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			(*mSelected)->setVelocity(sf::Vector2f(0.f, -speed));
		}

		// Rotation
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		{
			(*mSelected)->rotate(2.f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		{
			(*mSelected)->rotate(-2.f);
		}
	}

}

void Demo::render(sf::RenderWindow& window)
{
	window.draw(mSceneGraph);
}