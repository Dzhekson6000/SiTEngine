#ifndef LABEL_H_
#define LABEL_H_

#include "Base/Node.h"
#include <string>

#include "Resource/ResourceManager.h"



NS_SIT_BEGIN

class SIT_DLL Label : public Node
{
public:
	static Label* create();
	static Label* create(std::string text);
	static Label* create(std::string text, unsigned int sizeFont);

	virtual ~Label();

	virtual void	draw(Renderer *renderer);
	virtual void	onDraw();
	void setColor(Color color);
	void drawFont();
protected:
	
private:
	Label(std::string text, unsigned int sizeFont);
	CustomCommand _customCommand;

	FontAtlas * _font;
	Color _color;
	unsigned int sizeFont;
	std::string _text;

	void	drawChar(Point point, CharacterInfo* info);
	const	Matrix4f* transform(Point point, CharacterInfo* info);

	unsigned int	_indices[6];
	GLuint			_IBO;
	Matrix4f		_transformation;
	
};


NS_SIT_END

#endif /* LABEL_H */