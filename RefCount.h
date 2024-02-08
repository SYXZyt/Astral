#pragma once

template <class T>
class RefCount final
{
private:
	int count;
	T* data;

public:
	static void AutoReleaseOrDelete(RefCount<T>* rc)
	{
		if (rc->CanDelete())
			delete rc;
		else
			rc->Release();
	}

	//Force delete a ref count while preserving data
	static void ForceDelete(RefCount<T>* rc)
	{
		rc->data = nullptr;
		delete rc;
	}

	void Add();
	void Release();

	inline T* Get() { return data; }

	inline void Update(T* newValue)
	{
		delete data;
		data = newValue;
	}

	inline bool CanDelete() const { return count <= 0; }

	RefCount();
	RefCount(T* data);

	~RefCount();
};