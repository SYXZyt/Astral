#pragma once
#pragma warning(push)
#pragma warning(disable : 4251)

#include <vector>

#include "Variable.h"
#include "../Memory/MemoryBlock.h"

namespace Astral
{
	class Variables final
	{
	private:
		//Use a vector since we need to be able to check each scope
		std::vector<std::vector<Variable*>> variables;

		bool DoesVariableExistInScope(const std::vector<Variable*>& scope, const char* vname);

	public:
		Variable* GetVariable(const char* name);
		Variable* GetVariableInGlobalScope(const char* name);

		bool DoesVariableExistInHighestScope(const char* name);
		bool DoesVariableExist(const char* name);
		void AddVariable(const char* vname);
		Variable* CreateVariableInGlobalScope(const char* vname);
		void UpdateValue(const char* vname, Type::atype_t* value);
		void UpdateRef(const char* vname, MemoryBlock* value);
		Type::atype_t* GetValue(const char* vname);

		void AddScope();
		void RemoveScope();

		Variables();
	};
}

#pragma warning(pop)