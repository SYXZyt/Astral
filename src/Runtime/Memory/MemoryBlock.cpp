#include "MemoryBlock.h"

#include "../Variables/Variable.h"

void Astral::MemoryBlock::RemoveReference(Variable* variable)
{
	for (int i = (int)referencing.size() - 1; i >= 0; i--)
	{
		if (referencing[i] == variable)
			referencing.erase(referencing.begin() + i);
	}
}