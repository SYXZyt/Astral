#include "GarbageCollector.h"

#ifdef _DEBUG
#ifdef _WIN32
#include <Windows.h>
#endif
#endif

Astral::GarbageCollector* Astral::GarbageCollector::instance = nullptr;

Astral::MemoryBlock* Astral::GarbageCollector::New()
{
    MemoryBlock* block = new MemoryBlock(new Type::void_t());
	memory.push_back(block);
	return block;
}

void Astral::GarbageCollector::Cleanup()
{
#ifdef _DEBUG
#ifdef _WIN32
	OutputDebugStringA("=== ASTRAL GC BEGIN ===\n");
#endif
#endif

#ifdef _DEBUG
#ifdef _WIN32
	int blocksCleared = 0;
#endif
#endif

	for (int i = memory.size() - 1; i >= 0; i--)
	{
		//If a block has no references, it can be deleted
		if (memory[i]->CanDelete())
		{
			memory.erase(memory.begin() + i);

#ifdef _DEBUG
#ifdef _WIN32
			++blocksCleared;
#endif
#endif
		}
	}

#ifdef _DEBUG
#ifdef _WIN32
	std::string s = "\tGC: Cleared " + std::to_string(blocksCleared) + " blocks\n";
	OutputDebugStringA(s.c_str());
	blocksCleared = 0;
#endif
#endif

	//Estimate how many kbs are in use. Since different types have a differnt size, this is only a minimum, but it will be good enough
	unsigned int size = (danglingMemory.size() * sizeof(Type::atype_t)) / 1024;
	if (size >= CullLimit) //If we have too much memory, all of the data we can
	{
		for (int i = danglingMemory.size() - 1; i >= 0; i--)
		{
			if (!danglingMemory[i]->isOnStack) //If this is not on the stack, then we know it is not in use and ready to be cleaned up
			{
				danglingMemory.erase(danglingMemory.begin() + i);
#ifdef _DEBUG
#ifdef _WIN32
				++blocksCleared;
#endif
#endif
			}
		}
	}

#ifdef _DEBUG
#ifdef _WIN32
	s = "\tGC: Cleared " + std::to_string(blocksCleared) + " pointers\n";
	OutputDebugStringA(s.c_str());
	OutputDebugStringA("=== ASTRAL GC END ===\n");
#endif
#endif
}

void Astral::GarbageCollector::RegisterDanglingPointer(Type::atype_t* data)
{
	danglingMemory.push_back(data);
}

void Astral::GarbageCollector::RemoveDanglingPointer(Type::atype_t* data)
{
	for (int i = danglingMemory.size() - 1; i >= 0; i--)
	{
		if (danglingMemory[i] == data)
		{
			danglingMemory.erase(danglingMemory.begin() + i);
			return;
		}
	}
}

Astral::GarbageCollector::~GarbageCollector()
{
	for (MemoryBlock* block : memory)
		delete block;

	for (Type::atype_t* data : danglingMemory)
		delete data;
}