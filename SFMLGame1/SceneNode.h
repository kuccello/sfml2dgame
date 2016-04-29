#pragma once
/*
We represent the nodes in the scene graph with a class called SceneNode. Before we can implement it, we need 
to think about ownership semantics. The scene graph owns the scene nodes; therefore it is responsible for 
their lifetime and destruction. We want each node to store all its child nodes. If a node is destroyed, its 
children are destroyed with it. If the root is destroyed, the whole scene graph is torn down.

To store the children, we make use of the STL container std::vector. We cannot use std::vector<SceneNode>, 
since element types must be complete types (which they are only at the end of the SceneNode class definition, 
but not at the time of declaring the container as a member variable) and since our class is polymorphic 
(there will be derived classes overriding virtual functions of SceneNode). We could use std::vector<SceneNode*>, 
but then we would have to manage memory ourselves, so we take std::vector<std::unique_ptr<SceneNode>> instead. 
Since we are going to use the type std::unique_ptr<SceneNode> really often, we create a typedef for it, as a 
member inside the SceneNode class.

In addition to the children container, a pointer to the parent node is stored, so our class looks as follows:

*/
#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>

#include "Category.h"

#include <vector>
#include <memory>

struct Command;

class SceneNode : public sf::Transformable, public sf::Drawable, private sf::NonCopyable
{
public:
	typedef std::unique_ptr<SceneNode> Ptr;


public:
	SceneNode();

	void					attachChild(Ptr child);
	Ptr						detachChild(const SceneNode& node);

	void					update(sf::Time dt);

	sf::Vector2f			getWorldPosition() const;
	sf::Transform			getWorldTransform() const;

	virtual unsigned int	getCategory() const;
	void					onCommand(const Command& command, sf::Time dt);


private:
	virtual void			updateCurrent(sf::Time dt);
	void					updateChildren(sf::Time dt);

	virtual void			draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void			drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	void					drawChildren(sf::RenderTarget& target, sf::RenderStates states) const;


private:
	std::vector<Ptr>		mChildren;
	SceneNode*				mParent;
};