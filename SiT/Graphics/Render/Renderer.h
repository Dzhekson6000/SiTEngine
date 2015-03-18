#ifndef RENDERER_H_
#define RENDERER_H_

#include "Macros.h"
#include <vector>
#include <algorithm>

#include "Command/CustomCommand.h"


NS_SIT_BEGIN

class RenderQueue {

public:
	void push_back(RenderCommand* command);
	size_t size() const;
	void sort();
	RenderCommand* operator[](size_t index) const;
	void clear();

protected:
	std::vector<RenderCommand*> _queueNegZ;
	std::vector<RenderCommand*> _queue0;
	std::vector<RenderCommand*> _queuePosZ;
};


class Renderer
{
private:
	bool _isRendering;
	std::vector<RenderQueue> _renderGroups;
public:
	Renderer();
	~Renderer();

	static const int VBO_SIZE = 65536 / 6;

	void addCommand(RenderCommand* command);

	void visitRenderQueue(const RenderQueue& queue);
	void render();
	void clean();
};

NS_SIT_END

#endif