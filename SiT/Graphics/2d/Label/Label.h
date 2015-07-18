#ifndef LABEL_H_
#define LABEL_H_

#include "Base/Node.h"
#include <string>

#include "Resource/ResourceManager.h"
#include "Resource/Matrix/MatrixObject.h"


NS_SIT_BEGIN

class SIT_DLL Label : public Node
{
public:

	enum TextAlignmentHorizontal {
		TEXT_ALIGN_LEFT,
		TEXT_ALIGN_CENTER,
		TEXT_ALIGN_RIGHT,
		TEXT_ALIGN_MAX
	};

	static Label* create();
	static Label* create(std::string text);
	static Label* create(std::string text, unsigned int sizeFont);

	virtual ~Label();

	virtual void	draw(Renderer *renderer);
	virtual void	onDraw();
	void setColor(Color color);
	void setSize(unsigned int sizeFont);
	void setText(std::string text);
	void setAlignmentHorizontal(TextAlignmentHorizontal textAlignmentHorizontal);
	void drawFont();
protected:
	
private:
	Label(std::string text, unsigned int sizeFont);
	CustomCommand _customCommand;

	FontAtlas * _font;
	Color _color;
	unsigned int _sizeFont;
	TextAlignmentHorizontal _textAlignmentHorizontal;
	std::string _text;

	void	drawChar(Point point, CharacterInfo* info);
	Matrix<4,4,float> transform(Point point, CharacterInfo* info);

	unsigned int	_indices[6];
	GLuint			_IBO;
	
};


NS_SIT_END

#endif /* LABEL_H */