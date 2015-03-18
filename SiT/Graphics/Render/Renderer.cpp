#include "Renderer.h"

NS_SIT_BEGIN

static bool compareRenderCommand(RenderCommand* a, RenderCommand* b)
{
	return a->getGlobalOrder() < b->getGlobalOrder();
}

void RenderQueue::push_back(RenderCommand* command)
{
	float z = command->getGlobalOrder();
	if(z < 0)
		_queueNegZ.push_back(command);
	else if(z > 0)
		_queuePosZ.push_back(command);
	else
		_queue0.push_back(command);
}

size_t RenderQueue::size() const
{
	return _queueNegZ.size() + _queue0.size() + _queuePosZ.size();
}

void RenderQueue::sort()
{
	std::sort(std::begin(_queueNegZ), std::end(_queueNegZ), compareRenderCommand);
	std::sort(std::begin(_queuePosZ), std::end(_queuePosZ), compareRenderCommand);
}

RenderCommand* RenderQueue::operator[](size_t index) const
{
	if(index < static_cast<size_t>(_queueNegZ.size()))
		return _queueNegZ[index];

	index -= _queueNegZ.size();

	if(index < static_cast<size_t>(_queue0.size()))
		return _queue0[index];

	index -= _queue0.size();

	if(index < static_cast<size_t>(_queuePosZ.size()))
		return _queuePosZ[index];

	return nullptr;
}

void RenderQueue::clear()
{
	_queueNegZ.clear();
	_queue0.clear();
	_queuePosZ.clear();
}

Renderer::Renderer():_isRendering(false)
{
	RenderQueue defaultRenderQueue;
	_renderGroups.push_back(defaultRenderQueue);
}

Renderer::~Renderer()
{
	_renderGroups.clear();
}

void Renderer::addCommand( RenderCommand* command )
{
	_renderGroups[0].push_back(command);
}

void Renderer::visitRenderQueue(const RenderQueue& queue)
{
	size_t size = queue.size();
	for (size_t index = 0; index < size; ++index)
	{
		auto command = queue[index];
		auto commandType = command->getType();
		if(RenderCommand::Type::CUSTOM_COMMAND == commandType)
		{
			auto cmd = static_cast<CustomCommand*>(command);
			cmd->execute();
		}
	}
}

void Renderer::render()
{
	_isRendering = true;
	for (auto &renderqueue : _renderGroups)
	{
		renderqueue.sort();
	}
	visitRenderQueue(_renderGroups[0]);
	clean();
	_isRendering = false;
}

void Renderer::clean()
{
	for (size_t j = 0 ; j < _renderGroups.size(); j++)
	{
		_renderGroups[j].clear();
	}
}

NS_SIT_END