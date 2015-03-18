#ifndef SHADERMANAGER_H_
#define SHADERMANAGER_H_

#include "Base/Ref.h"
#include "Shader.h"
#include "Shaders.h"

#include <string>
#include <unordered_map>

NS_SIT_BEGIN

class SIT_DLL ShaderManager: public Ref
{
private:
	bool init();
	void loadDefaultShader(Shader* program, int type);

	std::unordered_map<std::string, Shader*> _shaders;
public:
	ShaderManager();
	virtual ~ShaderManager();

	static ShaderManager* getInstance();
	static void destroyInstance();

	void loadDefaultShaders();
	void reloadDefaultShaders();

	Shader* getShader(const std::string &key);

};

NS_SIT_END


#endif // SHADERMANAGER_H_