#pragma once
#include <vector>

#include "MemoryBlock.h"

namespace Astral
{
	class GarbageCollector final
	{
	private:
		std::vector<MemoryBlock*> memory;
		std::vector<Type::atype_t*> danglingMemory; //This is for generic data which is not owned by a variable. It will get buffered into here to be deleted when a threshold is met

		static GarbageCollector* instance;

		static constexpr unsigned int CullLimit = 1000; //In kb

	public:
		static void FreeInstance()
		{
			delete instance;
			instance = nullptr;
		}

		static GarbageCollector& Instance()
		{
			if (!instance)
				instance = new GarbageCollector();

			return *instance;
		}

		MemoryBlock* New();

		void Cleanup();

		void RegisterDanglingPointer(Type::atype_t* data);
		void RemoveDanglingPointer(Type::atype_t* data);

		~GarbageCollector();
	};
}