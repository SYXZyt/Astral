#pragma once
#include <stack>
#include <vector>
#include <iostream>

#include "../Astral.h"
#include "MathsHandler.h"
#include "BooleanHandler.h"
#include "../ErrorManager.h"
#include "Types/AstralTypes.h"
#include "Variables/Variables.h"
#include "../Compilation/Compiler/OpType.h"
#include "../Compilation/Compiler/Bytecode.h"

namespace Astral
{
	class ASTRAL Interpreter final
	{
	private:
		inline std::shared_ptr<Type::atype_t> Pop()
		{
			std::shared_ptr<Type::atype_t> value = stack.top();
			stack.pop();
			return value;
		}

		Variables variables;

		std::stack<std::shared_ptr<Type::atype_t>> stack;

		std::vector<Bytecode> rom;
		int pc;

		bool failed;

		void ExecuteInstruction(Bytecode& instruction);

	public:
		void Execute();

		inline bool Failed() const { return failed; }

		Interpreter(const std::vector<Bytecode>& rom) : rom(rom), pc(0), failed(false) {}
		~Interpreter();
	};
}