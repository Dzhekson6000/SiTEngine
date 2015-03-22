#include "Node.h"

NS_SIT_BEGIN

Node::Node():
_parent(nullptr),_screenSize(nullptr)
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

const Size* Node::getScreenSize()
{
	if(_screenSize == nullptr)
	{
		_screenSize = Director::getInstance()->getWinSize();
	}
	return _screenSize;
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
	_scale = scale;
}

void Node::setPosition( const Point &point )
{
	_point = point;
}

void Node::setSize( const Size &size )
{
	_size = size;
}

void Node::setScreenSize(Size* size )
{
	_screenSize = size;
}

void Node::setRotation( const Rotate &rotate )
{
	_rotate = rotate;
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