#include "Node.h"

NS_SIT_BEGIN

Node::Node():
_parent(nullptr)
{

}

Node::~Node()
{

}

bool Node::init()
{
	return true;
}

Node* Node::getScene()
{
	if(!_parent)
		return nullptr;

	return _parent->getScene();
}

const Scale& Node::getScale() const
{
	return _scale;
}

const Point& Node::getPosition() const
{
	return _point;
}

const Size& Node::getSize() const
{
	return _size;
}

const Rotate& Node::getRotation() const
{
	return _rotate;
}

const Node* Node::getParent() const
{
	return _parent;
}

const int Node::getLocalZOrder()
{
	return _localZOrder;
}

size_t Node::getChildrenCount() const
{
	return _children.size();
}

void Node::setScale( const Scale &scale )
{

}

void Node::setPosition( const Point &point )
{

}

void Node::setSize( const Size &size )
{

}

void Node::setContentSize( const Size &size )
{

}

void Node::setRotation( const Rotate &rotate )
{

}

void Node::setLocalZOrder( int localZOrder )
{
	_localZOrder = localZOrder;
}

void Node::setParent(Node* parent )
{
	_parent = parent;
}

void Node::addChild( Node* child )
{
	if(child==nullptr)return;
	this->addChild(child, child->_localZOrder);
}

void Node::addChild( Node* child, int localZOrder )
{
	if(child==nullptr)return;

	_children.push_back(child);
	child->setLocalZOrder(localZOrder);

}

void Node::removeChild( Node* child, bool cleanup /*= true*/ )
{

}

void Node::removeAllChildren()
{

}

void Node::draw(Renderer *renderer)
{

}

void Node::visit()
{
	auto renderer = Director::getInstance()->getRenderer();
}

void Node::visit(Renderer *renderer)
{
	if (!_visible)return;
	
	if(!_children.empty())
	{
		for(auto child:_children)
		{
			child->visit(renderer);
		}
	}
	this->draw(renderer);
}

void Node::cleanup()
{

}

NS_SIT_END