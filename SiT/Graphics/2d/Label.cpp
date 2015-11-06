#include "Label.h"

NS_SIT_BEGIN

Label* Label::create(std::string pathFont)
{
	auto ret = new Label("", pathFont, DEFAULT_SIZE_FONT);
	if (ret && ret->init())
	{
		ret->autorelease();
		return ret;
	}
	return nullptr;
}

Label* Label::create(std::string text, std::string pathFont)
{
	auto ret = new Label(text, pathFont, DEFAULT_SIZE_FONT);
	if (ret && ret->init())
	{
		ret->autorelease();
		return ret;
	}
	return nullptr;
}

Label* Label::create(std::string text, std::string pathFont, unsigned int sizeFont)
{
	auto ret = new Label(text, pathFont, sizeFont);
	if (ret && ret->init())
	{
		ret->autorelease();
		return ret;
	}
	return nullptr;
}

Label::Label(std::string text, std::string pathFont, unsigned int sizeFont) :
_text(text), _pathFont(pathFont), _sizeFont(sizeFont), _transformCharacters(nullptr), _isUpdatedCharacters(false)
{
}

bool Label::init()
{
	_font = (FontAtlas *)ResourceManager::getInstance()->getHandle(new Resource(_pathFont));

	_textAlignmentHorizontal = TEXT_ALIGN_LEFT;

	_indices[0] = 0;
	_indices[1] = 1;
	_indices[2] = 2;
	_indices[3] = 2;
	_indices[4] = 3;
	_indices[5] = 0;

	GRAPHICS_LIB()->genBuffers(1, &_IBO);
	GRAPHICS_LIB()->bindBuffer(GraphicsLib::TargetBuffer::ELEMENT_ARRAY_BUFFER, _IBO);
	GRAPHICS_LIB()->bufferData(GraphicsLib::TargetBuffer::ELEMENT_ARRAY_BUFFER, sizeof(_indices), _indices, GraphicsLib::UsageStore::STATIC_DRAW);

	_shader = _font->getShader();
	setText(_text);
	return true;
}

Label::~Label()
{
	GRAPHICS_LIB()->deleteBuffers(1, &_IBO);
}

const Matrix<4, 4, float>* Label::transform()
{
	if (_isUpdated)return &_transformation;
	Size* screen = getScreenSize();

	MatrixObject scale, rotate, translation;
	scale.initScaleTransform(_scale);
	rotate.initRotateTransform(_rotate);

	translation.initTranslationTransform(
		_point.getX() / (screen->getWidth() / 2 * _parent->getAbsoluteScaleX()),
		_point.getY() / (screen->getHeight() / 2 * _parent->getAbsoluteScaleY()),
		_point.getZ()
		);

	_transformation = scale * rotate * translation * _parent->getTransformation();

	_isUpdated = true;
	Node::transform();

	return &_transformation;
}

Matrix<4, 4, float>* Label::transformCharacter(unsigned int position, Point point, CharacterInfo* info)
{
	if (_isUpdatedCharacters && _transformCharacters[position] != nullptr) return _transformCharacters[position];
	Size* screen = getScreenSize();

	float scaleSizeFont = (float)_sizeFont / (float)_font->getSizeFont();

	MatrixObject scale, translation;
	scale.initScaleTransform(
		scaleSizeFont,
		scaleSizeFont,
		_scale.getZ()
		);


	translation.initTranslationTransform(
		point.getX() / (screen->getWidth() / 2 * _parent->getAbsoluteScaleX()),
		point.getY() / (screen->getHeight() / 2 * _parent->getAbsoluteScaleY()),
		point.getZ()
	);

	if (_transformCharacters[position] == nullptr) _transformCharacters[position] = new Matrix < 4, 4, float >;
	*_transformCharacters[position] = translation * scale * *transform();

	return _transformCharacters[position];
}

void Label::computeSize()
{
	unsigned int widthLine = 0;
	unsigned int maxWidthLine = 0;
	
	float scaleSizeFont = (float)_sizeFont / (float)_font->getSizeFont();
	Scale scale(scaleSizeFont, scaleSizeFont);

	unsigned int heightLabel = (unsigned int)(_font->getLineSpacing()*scale.getY());
	
	GRAPHICS_LIB()->bindTexture((Texture*)_font->getTexture());

	for (unsigned int i = 0; i < _text.size(); i++)
	{
		if (widthLine == 0)
		{
			for (unsigned int j = i; j < _text.size(); j++)
			{
				unsigned int char_ = _text[j];
				if (char_ == '\n')
				{
					heightLabel += (unsigned int)(_font->getLineSpacing()*scale.getY());
					if (maxWidthLine < widthLine)maxWidthLine = widthLine;
					break;
				}
				CharacterInfo* info = _font->getInfoChar(char_);
				widthLine += (unsigned int)(info->advance.getX()*scale.getX());
			}
			if (maxWidthLine == 0)maxWidthLine = widthLine;
		}
	}

	_size.setWidth(maxWidthLine);
	_size.setHeight(heightLabel);
}

unsigned int Label::computeWidthLine(unsigned int position)
{
	unsigned int widthLine = 0;
	for (unsigned int j = position; j < _text.size(); j++)
	{
		unsigned int char_ = _text[j];
		if (char_ == '\n')break;
		CharacterInfo* info = _font->getInfoChar(char_);
		widthLine += (unsigned int)info->advance.getX();
	}
	return widthLine;
}

void Label::onDraw()
{
	if (!_isUpdated)_isUpdatedCharacters = false;
	_shader->use();

	GRAPHICS_LIB()->enableAlpha();

	GRAPHICS_LIB()->activeTexture(0);
	GRAPHICS_LIB()->bindTexture((Texture*)_font->getTexture());

	int offsetX = 0;
	int offsetY = 0;
	int widthLine = 0;

	for (unsigned int i = 0; i < _text.size(); i++)
	{
		if (widthLine == 0)widthLine = computeWidthLine(i);

		unsigned int char_ = _text[i];
		CharacterInfo* info = _font->getInfoChar(char_);

		if (char_ == '\n')
		{
			widthLine = 0;
			offsetX = 0;
			offsetY += _font->getLineSpacing();
			continue;
		}

		Point point;

		switch (_textAlignmentHorizontal)
		{
		case Label::TEXT_ALIGN_LEFT:
			point = Point(
				offsetX + info->bearing.getX() + info->size.getWidth() / 2,
				-offsetY + (-info->size.getHeight() / 2 + info->bearing.getY()));
			break;
		case Label::TEXT_ALIGN_CENTER:
			point = Point(
				offsetX + info->bearing.getX() + info->size.getWidth() / 2 - widthLine/2,
				-offsetY + (-info->size.getHeight() / 2 + info->bearing.getY()));
			break;
		case Label::TEXT_ALIGN_RIGHT:
			point = Point(
				offsetX + info->bearing.getX() + info->size.getWidth() / 2 - widthLine,
				-offsetY + (-info->size.getHeight() / 2 + info->bearing.getY()));
			break;
		case Label::TEXT_ALIGN_MAX:
			break;
		default:
			break;
		}

		drawChar(i, point,info);

		offsetX += (int)info->advance.getX();
		offsetY += (int)info->advance.getY();
	}
	
	GRAPHICS_LIB()->disableAlpha();
	_isUpdatedCharacters = true;
}

void Label::setSize(unsigned int sizeFont)
{
	_sizeFont = sizeFont;
	computeSize();
	_isUpdated = false;
}

void Label::setText(std::string text)
{
	_text = text;
	computeSize();
	if (_transformCharacters != nullptr){
		for (unsigned int i = 0; i < _text.size(); i++)
		{
			if (_transformCharacters[i] != nullptr) delete _transformCharacters[i];
		}
		delete[] _transformCharacters;
	}
	_transformCharacters = new Matrix<4, 4, float>*[_text.size()];
	for (unsigned int i = 0; i < _text.size(); i++)_transformCharacters[i] = nullptr;
	_isUpdated = false;
}

void Label::setAlignmentHorizontal(TextAlignmentHorizontal textAlignmentHorizontal)
{
	_textAlignmentHorizontal = textAlignmentHorizontal;
	_isUpdated = false;
}

void Label::drawChar(unsigned int position, Point point, CharacterInfo* info)
{
	GLfloat color[4] = { _color.getR(), _color.getG(), _color.getB(), 1 };

	_shader->setUniformLocationWith1i(_shader->getUniformLocation(_shader->UNIFORM_NAME_SAMPLER), 0);
	_shader->setUniformLocationWith4fv(_shader->getUniformLocation(_shader->UNIFORM_NAME_COLOR), (const GLfloat*) color, 1);
	_shader->setUniformLocationWithMatrix4fv(_shader->getUniformLocation(_shader->UNIFORM_NAME_MVP_MATRIX), (const GLfloat*)transformCharacter(position, point, info), 1);
	
	GRAPHICS_LIB()->bindBuffer(GraphicsLib::TargetBuffer::ARRAY_BUFFER, info->_VBO);

	GRAPHICS_LIB()->vertexAttribPointer(_shader->VERTEX_ATTRIB_POSITION, 3, GraphicsLib::DataType::FLOAT, false, sizeof(Vertex), nullptr);
	GRAPHICS_LIB()->vertexAttribPointer(_shader->VERTEX_ATTRIB_COLOR, 3, GraphicsLib::DataType::FLOAT, false, sizeof(Vertex), (void*)offsetof(Vertex, color));
	GRAPHICS_LIB()->vertexAttribPointer(_shader->VERTEX_ATTRIB_TEX_COORDS, 2, GraphicsLib::DataType::FLOAT, false, sizeof(Vertex), (void*)offsetof(Vertex, uv));

	GRAPHICS_LIB()->bindBuffer(GraphicsLib::TargetBuffer::ELEMENT_ARRAY_BUFFER, _IBO);
	GRAPHICS_LIB()->drawElements(GraphicsLib::RenderType::TRIANGLES, 6, GraphicsLib::DataType::UNSIGNED_INT, 0);
}

void Label::draw(Renderer *renderer)
{
	_customCommand.init(1);
	_customCommand.func = CALLBACK_0(Label::onDraw, this);
	renderer->addCommand(&_customCommand);
}

NS_SIT_END