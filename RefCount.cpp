#include "RefCount.h"

template<class T>
void RefCount<T>::Add()
{
	++count;
}

template<class T>
void RefCount<T>::Release()
{
	count--;

	if (count <= 0)
	{
		delete data;
		data = nullptr;
	}
}

template<class T>
RefCount<T>::RefCount() : count(0), data(nullptr) {}

template<class T>
RefCount<T>::RefCount(T* data) : count(0), data(data) {}

template<class T>
RefCount<T>::~RefCount()
{
	Release();
}