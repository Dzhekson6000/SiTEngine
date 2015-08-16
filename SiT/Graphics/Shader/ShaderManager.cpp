#include "ShaderManager.h"
#include "Libs/GraphicsLib.h"

NS_SIT_BEGIN

enum {
	shaderTypePositionColor,
	shaderTypePositionTexture,
	shaderTypePositionColorTexture,
	shaderType_MAX,
};

static ShaderManager* _shaderManager = nullptr;

ShaderManager* ShaderManager::getInstance()
{
	if (!_shaderManager) {
		_shaderManager = new ShaderManager();
		if (!_shaderManager->init())
		{
			delete _shaderManager;
			_shaderManager = nullptr;
		}
	}
	return _shaderManager;
}

void ShaderManager::destroyInstance()
{
	_shaderManager->release();
	_shaderManager = nullptr;
}

ShaderManager::ShaderManager(): _shaders()
{

}

ShaderManager::~ShaderManager()
{
	for( auto it = _shaders.begin(); it != _shaders.end(); ++it ) {
		(it->second)->release();
	}
}

bool ShaderManager::init()
{    
	loadDefaultShaders();
	return true;
}



void ShaderManager::loadDefaultShaders()
{
	Shader* shader = GRAPHICS_LIB()->createNewShader();
	loadDefaultShader(shader, shaderTypePositionColor);
	_shaders.insert( std::make_pair( Shader::SHADER_NAME_POSITION_COLOR, shader ) );

	shader = GRAPHICS_LIB()->createNewShader();
	loadDefaultShader(shader, shaderTypePositionTexture);
	_shaders.insert( std::make_pair( Shader::SHADER_NAME_POSITION_TEXTURE, shader ) );

	shader = GRAPHICS_LIB()->createNewShader();
	loadDefaultShader(shader, shaderTypePositionColorTexture);
	_shaders.insert(std::make_pair(Shader::SHADER_NAME_POSITION_COLOR_TEXTURE, shader));
}

void ShaderManager::reloadDefaultShaders()
{

}

void ShaderManager::loadDefaultShader(Shader *shader, int type)
{
	switch (type) {
	case shaderTypePositionColor:
		shader->initWithByteArrays(positionColorV, positionColorF);

		shader->bindAttribLocation(Shader::ATTRIBUTE_NAME_POSITION, Shader::VERTEX_ATTRIB_POSITION);
		shader->bindAttribLocation(Shader::ATTRIBUTE_NAME_COLOR, Shader::VERTEX_ATTRIB_COLOR);
		return;
		break;
	case shaderTypePositionTexture:
		shader->initWithByteArrays(positionTextureV, positionTextureF);

		shader->bindAttribLocation(Shader::ATTRIBUTE_NAME_POSITION, Shader::VERTEX_ATTRIB_POSITION);
		shader->bindAttribLocation(Shader::ATTRIBUTE_NAME_COLOR, Shader::VERTEX_ATTRIB_COLOR);
		shader->bindAttribLocation(Shader::ATTRIBUTE_NAME_TEX_COORD, Shader::VERTEX_ATTRIB_TEX_COORDS);

		break;
	case shaderTypePositionColorTexture:
		shader->initWithByteArrays(positionColorTextureV, positionColorTextureF);

		shader->bindAttribLocation(Shader::ATTRIBUTE_NAME_POSITION, Shader::VERTEX_ATTRIB_POSITION);
		shader->bindAttribLocation(Shader::ATTRIBUTE_NAME_COLOR, Shader::VERTEX_ATTRIB_COLOR);
		shader->bindAttribLocation(Shader::ATTRIBUTE_NAME_TEX_COORD, Shader::VERTEX_ATTRIB_TEX_COORDS);

		break;
	}

	shader->link();
	shader->updateUniforms();
}

Shader* ShaderManager::getShader(const std::string &key)
{
	auto it = _shaders.find(key);
	if( it != _shaders.end() )
		return it->second;
	return nullptr;
}

NS_SIT_END