#include "SceneNode.h"

#include <algorithm>
#include <cassert>

SceneNode::SceneNode() 
: mChildren()
, mParent(nullptr)
, mType(TYPE::None)
{

}

void SceneNode::attachChild(SceneNode::Ptr child) 
{
	child->mParent = this;
	mChildren.push_back(std::move(child));
}

SceneNode::Ptr SceneNode::detachChild(const SceneNode& node) 
{
	// look through mchildren using lambda function as search criteria
	// [&] captures all variables by reference
	auto found = std::find_if(mChildren.begin(), mChildren.end(),
		[&](Ptr& p) -> bool { return p.get() == &node; });

	// should not be trying to detach nonexistent nodes
	assert(found != mChildren.end()); 

	// detach and return result
	Ptr result = std::move(*found); // found now points to nothing
	result->mParent = nullptr;
	mChildren.erase(found); // delete null child
	return result;

}

void SceneNode::kill() {
	mParent->detachChild(*this);
	mParent = nullptr;
}


void SceneNode::setType(TYPE type)
{
	mType = type;
}

SceneNode::TYPE SceneNode::getType()
{
	return mType;
}

void SceneNode::getChildren(std::vector<SceneNode*>& children)
{
	for (SceneNode::Ptr& child : mChildren)
	{
		children.push_back(child.get());
	}
}

bool SceneNode::isOrphan()
{
	return mParent == nullptr;
}

void SceneNode::update(sf::Time dt) 
{
	updateCurrent(dt);
	updateChildren(dt);
}

void SceneNode::updateCurrent(sf::Time dt)
{
	// do nothing by default
}

void SceneNode::updateChildren(sf::Time dt)
{
	for (const SceneNode::Ptr& child : mChildren)
	{
		child->update(dt);
	}
}

void SceneNode::draw(sf::RenderTarget& target, 
					 sf::RenderStates states) const 
{
	// apply transform of current node
	states.transform *= getTransform();

	// draw
	drawCurrent(target, states);
	drawChildren(target, states);
}

void SceneNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates States) const
{
	// do nothing by default
}

void SceneNode::drawChildren(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (const SceneNode::Ptr& child : mChildren)
	{
		child->draw(target, states);
	}
}