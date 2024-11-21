#pragma once
#include <list>

template<class Object>
class RTArray
{
public:
	RTArray(Object* instance, size_t size);
	~RTArray();
public:
	const Object& GetNext() const;
	const Object& GetOldestUsed() const;
	void PutBack(Object* instance);
private:
	Object** m_pool;
	std::list<Object> m_inuse;
	size_t m_size;
	unsigned int m_available;
	bool m_supportRecycle;
};