#pragma once
#include <vector>

#include "Variable.h"

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

		bool DoesVariableExistInHighestScope(const char* name);
		bool DoesVariableExist(const char* name);
		void AddVariable(const char* vname);
		void UpdateValue(const char* vname, std::shared_ptr<Type::atype_t> value);
		std::shared_ptr<Type::atype_t> GetValue(const char* vname);

		void AddScope();
		void RemoveScope();

		Variables();
	};
}