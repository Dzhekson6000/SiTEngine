#include "PoolManager.h"

NS_SIT_BEGIN

AutoreleasePool::AutoreleasePool()
{
	_managedObjects.reserve(150);
	PoolManager::getInstance()->push(this);
}

AutoreleasePool::~AutoreleasePool()
{
	clear();
	PoolManager::getInstance()->pop();
}

void AutoreleasePool::addObject(Ref* object)
{
	_managedObjects.push_back(object);
}

void AutoreleasePool::clear()
{
	for (const auto &obj : _managedObjects)
	{
		obj->release();
	}
	_managedObjects.clear();
}

bool AutoreleasePool::isContains(Ref* object) const
{
	for (const auto& obj : _managedObjects)
	{
		if (obj == object)
			return true;
	}
	return false;
}

//--------------------------------------------------------------------
//
// PoolManager
//
//--------------------------------------------------------------------

PoolManager* PoolManager::_poolManager = nullptr;

PoolManager* PoolManager::getInstance()
{
	if (_poolManager == nullptr)
	{
		_poolManager = new PoolManager();
		_poolManager->_curReleasePool = new AutoreleasePool();
		_poolManager->_releasePoolStack.push_back(_poolManager->_curReleasePool);
	}
	return _poolManager;
}

void PoolManager::destroyInstance()
{
	delete _poolManager;
	_poolManager = nullptr;
}

PoolManager::PoolManager()
{
}

PoolManager::~PoolManager()
{
	while (!_releasePoolStack.empty())
	{
		AutoreleasePool* pool = _releasePoolStack.back();
		_releasePoolStack.pop_back();
		delete pool;
	}
}

AutoreleasePool* PoolManager::getCurrentPool() const
{
	return _curReleasePool;
}

bool PoolManager::isObjectInPools(Ref* obj) const
{
	for (const auto& pool : _releasePoolStack)
	{
		if (pool->isContains(obj))
			return true;
	}
	return false;
}

void PoolManager::push(AutoreleasePool *pool)
{
	_releasePoolStack.push_back(pool);
	_curReleasePool = pool;
}

void PoolManager::pop()
{
	_releasePoolStack.pop_back();

	if (_releasePoolStack.size() > 1)
	{
		_curReleasePool = _releasePoolStack.back();
	}
}

NS_SIT_END