#pragma once
#pragma warning(push)
#pragma warning(disable : 4251)

#include <vector>

#include "../Types/AstralTypes.h"

namespace Astral
{
	class Variable;

	struct MemoryBlock
	{
		std::vector<Variable*> referencing; //All of the variables who are pointing to this

		Type::atype_t* data;

		bool CanDelete() const { return referencing.size() == 0; }

		void RemoveReference(Variable* variable);

		explicit MemoryBlock(Type::atype_t* data) : data(data) {}
		~MemoryBlock() { delete data; }
	};
}

#pragma warning(pop)