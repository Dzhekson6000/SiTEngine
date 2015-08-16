#include "Node.h"

NS_SIT_BEGIN

Node::Node() :
_parent(nullptr), _screenSize(nullptr), _visible(true), _isUpdated(false)
{
	_transformation.initIdentity();
}

Node::~Node()
{

}

bool Node::init()
{
	return true;
}

float Node::getAbsoluteScaleX()
{
	return _parent != nullptr ? _scale.getX() * _parent->getAbsoluteScaleX() : _scale.getX();
}

float Node::getAbsoluteScaleY()
{
	return _parent != nullptr ? _scale.getY() * _parent->getAbsoluteScaleY() : _scale.getY();
}

Node* Node::getScene()
{
	if(!_parent)
		return nullptr;

	return _parent->getScene();
}

Scale& Node::getScale()
{
	return _scale;
}

Point& Node::getPosition()
{
	return _point;
}

Size& Node::getSize()
{
	return _size;
}

Size* Node::getScreenSize()
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

const Matrix<4, 4, float>* Node::transform()
{
	if (_isUpdated)return &_transformation;



	return &_transformation;
}

Matrix<4, 4, float> Node::getTransformation()
{
	transform();
	return _transformation;
}

void Node::setScale(const Scale &scale)
{
	_scale = scale;
	_isUpdated = false;
}

void Node::setPosition( const Point &point )
{
	_point = point;
	_isUpdated = false;
}

void Node::setSize( const Size &size )
{
	_size = size;
	_isUpdated = false;
}

void Node::setScreenSize(Size* size )
{
	_screenSize = size;
	_isUpdated = false;
}

void Node::setRotation( const Rotate &rotate )
{
	_rotate = rotate;
	_isUpdated = false;
}

void Node::setLocalZOrder( int localZOrder )
{
	_localZOrder = localZOrder;
}

void Node::setParent(Node* parent )
{
	_parent = parent;
	_isUpdated = false;
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
	child->setParent(this);
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
	visit(renderer);
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