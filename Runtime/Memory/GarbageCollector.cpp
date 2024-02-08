#include "GarbageCollector.h"

Astral::GarbageCollector* Astral::GarbageCollector::instance = nullptr;

Astral::MemoryBlock* Astral::GarbageCollector::New()
{
    return new MemoryBlock(new Type::void_t());
}

void Astral::GarbageCollector::Cleanup()
{
	for (int i = memory.size() - 1; i >= 0; i--)
	{
		//If a block has no references, it can be deleted
		if (memory[i]->CanDelete())
			memory.erase(memory.begin() + i);
	}

	//Estimate how many kbs are in use. Since different types have a differnt size, this is only a minimum, but it will be good enough
	unsigned int size = (danglingMemory.size() * sizeof(Type::atype_t)) / 1024;
	if (size >= CullLimit) //If we have too much memory, all of the data we can
	{
		for (int i = danglingMemory.size() - 1; i >= 0; i--)
		{
			if (!danglingMemory[i]->isOnStack) //If this is not on the stack, then we know it is not in use and ready to be cleaned up
				danglingMemory.erase(danglingMemory.begin() + i);
		}
	}
}

void Astral::GarbageCollector::RegisterDanglingPointer(Type::atype_t* data)
{
	danglingMemory.push_back(data);
}

Astral::GarbageCollector::~GarbageCollector()
{
	for (MemoryBlock* block : memory)
		delete block;
}