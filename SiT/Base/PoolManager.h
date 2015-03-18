#ifndef POOLMANAGER_H_
#define POOLMANAGER_H_

#include "Macros.h"
#include <stack>
#include <vector>
#include "Ref.h"

NS_SIT_BEGIN

class SIT_DLL AutoreleasePool
{
public:
	AutoreleasePool();
	~AutoreleasePool();
	void addObject(Ref *object);
	void clear();
	bool isContains(Ref* object) const;
private:
    std::vector<Ref*> _managedObjects;
};

class SIT_DLL PoolManager
{
public:
	static PoolManager* getInstance();
	static void destroyInstance();
	AutoreleasePool *getCurrentPool() const;
	bool isObjectInPools(Ref* obj) const;
	friend class AutoreleasePool;
private:
	PoolManager();
	~PoolManager();

	void push(AutoreleasePool *pool);
	void pop();

	static PoolManager* _poolManager;

	std::deque<AutoreleasePool*> _releasePoolStack;
	AutoreleasePool *_curReleasePool;
};

NS_SIT_END

#endif// POOLMANAGER_H_