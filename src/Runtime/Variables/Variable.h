#pragma once
#pragma warning(push)
#pragma warning(disable : 4251)

#include "../../Astral.h"
#include "../Types/AstralTypes.h"
#include "../Memory/GarbageCollector.h"

namespace Astral
{
	struct MemoryBlock;
	class ASTRAL Variable final
	{
	private:
		char* varname;
		MemoryBlock* value;

	public:
		inline const char* Name() const { return varname; }
		inline MemoryBlock* Value() { return value; }

		void SetValue(Type::atype_t* value);
		void SetValue(MemoryBlock* value);

		Variable(const char* name);
		~Variable();
	};
}

#pragma warning(pop)