#include "GarbageCollector.h"

Astral::GarbageCollector* Astral::GarbageCollector::instance = nullptr;

Astral::MemoryBlock* Astral::GarbageCollector::New()
{
    return new MemoryBlock(nullptr);
}

void Astral::GarbageCollector::Cleanup()
{
	for (int i = memory.size() - 1; i >= 0; i--)
	{
		//If a block has no references, it can be deleted
		if (memory[i]->CanDelete())
			memory.erase(memory.begin() + i);
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