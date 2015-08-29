#ifndef LABEL_H_
#define LABEL_H_

#include "Base/Node.h"
#include <string>

#include "Resource/ResourceManager.h"
#include "Resource/FontAtlas.h"


NS_SIT_BEGIN

class SIT_DLL Label : public Node
{
private:
								Label(std::string text, std::string pathFont, unsigned int sizeFont);
	void						drawChar(Point point, CharacterInfo* info);

	
	const Matrix<4, 4, float>*	transform();
	Matrix<4, 4, float>			transformCharacter(Point point, CharacterInfo* info);

	
	CustomCommand				_customCommand;
	Matrix<4, 4, float>*		_transformCharacters;

	unsigned int				_indices[6];
	GLuint						_IBO;

	std::string					_text;
	std::string					_pathFont;
	unsigned int				_sizeFont;
	FontAtlas*					_font;

	SYNTHESIZE(Color, _color, Color);
public:

	enum TextAlignmentHorizontal {
		TEXT_ALIGN_LEFT,
		TEXT_ALIGN_CENTER,
		TEXT_ALIGN_RIGHT,
		TEXT_ALIGN_MAX
	};

	static Label*				create(std::string pathFont);
	static Label*				create(std::string text, std::string pathFont);
	static Label*				create(std::string text, std::string pathFont, unsigned int sizeFont);
	virtual bool				init();

	virtual						~Label();

	virtual void				draw(Renderer *renderer);
	virtual void				onDraw();
	void						setSize(unsigned int sizeFont);
	void						setText(std::string text);
	void						setAlignmentHorizontal(TextAlignmentHorizontal textAlignmentHorizontal);
	void						drawFont();
protected:
	
private:
	TextAlignmentHorizontal _textAlignmentHorizontal;
};


NS_SIT_END

#endif /* LABEL_H */