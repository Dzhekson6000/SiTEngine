#ifndef NODE_H_
#define NODE_H_

#include "Director.h"
#include "Ref.h"
#include <vector>
#include "Types/Types.h"
#include "Base/PoolManager.h"
#include "Graphics/Shader/ShaderManager.h"
#include "Types/Matrix/MatrixObject.h"

NS_SIT_BEGIN

class Node: public Ref
{
private:
	
protected:
	Scale				_scale;
	Point				_point;
	Size				_size;
	Size*				_screenSize;
	Rotate				_rotate;
	std::vector<Node*>	_children;
	Node*				_parent;
	int					_localZOrder;
	bool				_visible;
	Shader*				_shader;
	Matrix<4, 4, float> _transformation;
	bool				_isUpdated;

public:
	static Node* create(void);

	virtual Node*			getScene();
	virtual Scale&			getScale();
	virtual Point&			getPosition();
	virtual Size&			getSize();
	virtual	Size*			getScreenSize();
	virtual const Rotate&	getRotation() const;
	virtual const int		getLocalZOrder();
	virtual const Node*		getParent() const;
	virtual size_t			getChildrenCount() const;
	virtual const Matrix<4, 4, float>* transform();
	virtual Matrix<4, 4, float> getTransformation();

	float					getAbsoluteScaleX();
	float					getAbsoluteScaleY();

	virtual void			setScale(const Scale &scale);
	virtual void			setPosition(const Point &point);
	virtual void			setSize(const Size &size);
	virtual void			setScreenSize(Size* size);
	virtual void			setRotation(const Rotate &rotate);
	virtual void			setLocalZOrder(int localZOrder);
	virtual void			setParent(Node* parent);

	virtual void	addChild(Node* child);
	virtual void	addChild(Node* child, int localZOrder);

	virtual void	removeChild(Node* child, bool cleanup = true);
	virtual void	removeAllChildren();

	virtual void	draw(Renderer *renderer);
	virtual void	visit();
	virtual void	visit(Renderer *renderer);
	virtual void	cleanup();

	Node();
	virtual ~Node();

	virtual bool	init();
};

NS_SIT_END



#endif // NODE_H_