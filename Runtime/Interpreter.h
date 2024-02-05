#pragma once
#include <stack>
#include <vector>
#include <iostream>

#include "../Astral.h"
#include "MathsHandler.h"
#include "BooleanHandler.h"
#include "../ErrorManager.h"
#include "Types/AstralTypes.h"
#include "../Compilation/Compiler/OpType.h"
#include "../Compilation/Compiler/Bytecode.h"

namespace Astral
{
	class ASTRAL Interpreter final
	{
	private:
		inline Type::atype_t* Pop()
		{
			Type::atype_t* value = stack.top();
			stack.pop();
			return value;
		}

		std::stack<Type::atype_t*> stack;

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