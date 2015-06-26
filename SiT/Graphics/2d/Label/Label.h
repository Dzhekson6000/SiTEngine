#ifndef LABEL_H_
#define LABEL_H_

#include "Base/Node.h"
#include <string>

#include "Platform/win32/FileUtilsImpl.h"
#include "Resource/FontAtlas.h"



NS_SIT_BEGIN

class SIT_DLL Label : public Node
{
public:
	static Label* create();

	virtual ~Label();

	virtual void	draw(Renderer *renderer);
	virtual void	onDraw();
	void setColor(Color color);
	void drawFont();
protected:
	
private:
	Label();
	CustomCommand _customCommand;

	FontAtlas * _font;
	Color _color;

	void	drawChar(unsigned int char_);

	unsigned int _indices[6];
	GLuint	_IBO;
	Matrix4f _transformation;
	const Matrix4f* transform(CharacterInfo* info);
};


NS_SIT_END

#endif /* LABEL_H */