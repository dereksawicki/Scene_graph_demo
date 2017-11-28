#ifndef SCENE_NODE_H
#define SCENE_NODE_H


#include <SFML/Graphics.hpp>

#include <vector>
#include <memory>

class SceneNode : public sf::Drawable
				, public sf::Transformable
	            , public sf::NonCopyable 
{
public:
	typedef std::unique_ptr<SceneNode> Ptr;

public:
	enum TYPE {
		None, 
		Circle
	};


	SceneNode();

	void attachChild(Ptr child);
	Ptr detachChild(const SceneNode& node);

	void update(sf::Time dt);
	void kill();
	bool isOrphan();
	void SceneNode::getChildren(std::vector<SceneNode*>& children);
	TYPE getType();
	void setType(TYPE type);

private:
	virtual void updateCurrent(sf::Time dt);
	void updateChildren(sf::Time dt);

	/* const member function cannot call any non-const member functions,
	   nor can it change any member variables */
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	void drawChildren(sf::RenderTarget& target, sf::RenderStates states) const;


private:
	std::vector<Ptr> mChildren;
	SceneNode* mParent;
	TYPE mType;
};


#endif