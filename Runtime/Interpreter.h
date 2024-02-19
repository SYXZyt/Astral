#pragma once
#pragma warning(push)
#pragma warning(disable : 4251)

#include <stack>
#include <vector>
#include <iostream>

#include "../Astral.h"
#include "MathsHandler.h"
#include "BooleanHandler.h"
#include "../ErrorManager.h"
#include "Types/AstralTypes.h"
#include "Variables/Variables.h"
#include "Memory/GarbageCollector.h"
#include "../Compilation/Compiler/Rom.h"
#include "../Compilation/Compiler/OpType.h"
#include "../Compilation/Compiler/Bytecode.h"

namespace Astral
{
	class ASTRAL Interpreter final
	{
	private:
		static Interpreter* instance;

		inline void SkipBlock()
		{
			int nest = -1;

			while (true)
			{
				Bytecode& instruction = rom[pc];
				if (instruction.op == (uint8_t)OpType::SCOPE_BEG)
					++nest;
				if (instruction.op == (uint8_t)OpType::SCOPE_END)
				{
					if (nest == 0)
					{
						++pc;
						break;
					}
					--nest;
				}

				++pc;
			}
		}

		inline void While_JumpToBegin()
		{
			int nest = 0;

			while (true)
			{
				Bytecode& instruction = rom[pc];

				if (instruction.op == (uint8_t)OpType::WHILE_BEG)
				{
					if (nest == 0)
						break;

					--nest;
					break;
				}

				if (instruction.op == (uint8_t)OpType::WHILE_END)
					++nest;

				if (instruction.op == (uint8_t)OpType::SCOPE_BEG)
					variables.RemoveScope();

				if (instruction.op == (uint8_t)OpType::SCOPE_END)
					variables.AddScope();

				--pc;
			}
		}

		inline void While_ExitLoop()
		{
			while (true)
			{
				Bytecode& instruction = rom[pc];

				if (instruction.op == (uint8_t)OpType::WHILE_END)
				{
					++pc; //We don't want to execute the while end
					break;
				}

				if (instruction.op == (uint8_t)OpType::SCOPE_BEG)
					variables.AddScope();

				if (instruction.op == (uint8_t)OpType::SCOPE_END)
					variables.RemoveScope();

				++pc;
			}
		}

		inline bool IsInWhileLoop()
		{
			int instr = pc-1;
			int nest = 0;

			while (true)
			{
				//Begin back tracking tokens until we find while_start or the start of the rom
				//If we are at the start of the rom then we know we are not in a loop
				//In the future, we need to treat the start of a function as a "sub-program"
				//where the start of the function will return false
				if (rom[instr].op == (uint8_t)OpType::WHILE_BEG)
				{
					if (nest == 0)
						return true;

					--nest;
				}

				if (rom[instr].op == (uint8_t)OpType::WHILE_END)
					++nest;

				if (instr == 0)
					return false;

				--instr;
			}
		}

		inline Type::atype_t* Pop()
		{
			Type::atype_t* value = stack.top();
			stack.pop();
			value->isOnStack = false;
			return value;
		}

		inline void Push(Type::atype_t* value)
		{
			value->isOnStack = true;
			stack.push(value);
		}

		Variables variables;

		std::stack<Type::atype_t*> stack;

		std::vector<Bytecode> rom;
		Rom _rom;
		int pc;

		bool failed;

		void ExecuteInstruction(Bytecode& instruction);

	public:
		void Execute();

		inline bool Failed() const { return failed; }

		Interpreter(const Rom& rom) : rom(rom.GetRom()), _rom(rom), pc(0), failed(false)
		{
			instance = this;
		}

		~Interpreter();
	};
}

#pragma warning(pop)