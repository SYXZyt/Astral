#pragma once
#pragma warning(push)
#pragma warning(disable : 4251)

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


	public:
		static unsigned int CullLimit; //In kb

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

#pragma warning(pop)