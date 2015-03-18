#include "ShaderManager.h"

NS_SIT_BEGIN

enum {
	shaderTypePositionColor,
	shaderTypePositionTexture,
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
	Shader* shader = new Shader();
	loadDefaultShader(shader, shaderTypePositionColor);
	_shaders.insert( std::make_pair( Shader::SHADER_NAME_POSITION_COLOR, shader ) );

	shader = new Shader();
	loadDefaultShader(shader, shaderTypePositionTexture);
	_shaders.insert( std::make_pair( Shader::SHADER_NAME_POSITION_TEXTURE, shader ) );
}

void ShaderManager::reloadDefaultShaders()
{

}

void ShaderManager::loadDefaultShader(Shader *shader, int type)
{
	switch (type) {
	case shaderTypePositionColor:
		shader->initWithByteArrays(positionColorF, positionColorV);

		shader->bindAttribLocation(Shader::ATTRIBUTE_NAME_POSITION, Shader::VERTEX_ATTRIB_POSITION);
		shader->bindAttribLocation(Shader::ATTRIBUTE_NAME_COLOR, Shader::VERTEX_ATTRIB_COLOR);

		break;
	case shaderTypePositionTexture:
		shader->initWithByteArrays(positionTextureF, positionTextureV);

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