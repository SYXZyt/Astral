#pragma once
#pragma warning(push)
#pragma warning(disable : 4251)

#include <stack>
#include <vector>
#include <iostream>

#include "Library.h"
#include "../Astral.h"
#include "BindFunction.h"
#include "MathsHandler.h"
#include "BooleanHandler.h"
#include "../ErrorManager.h"
#include "BuiltInLibraries.h"
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

		inline void SkipFunction()
		{
			while (rom[pc].op != (uint8_t)OpType::FUNC_END)
				++pc;

			++pc; //Skip the func end
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

		inline void Func_CleanStackFrame()
		{
			while (rom[pc].op != (uint8_t)OpType::FUNC_BEG)
			{
				if (rom[pc].op == (uint8_t)OpType::SCOPE_END)
					variables.AddScope();
				else if (rom[pc].op == (uint8_t)OpType::SCOPE_BEG)
					variables.RemoveScope();

				--pc;
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

		std::stack<int> callstack;

		Type::atype_t* returnValue = nullptr;

		inline Type::atype_t* GetReturnValue()
		{
			returnValue->isOnStack = false;
			Type::atype_t* v = returnValue;
			returnValue = nullptr;
			return v;
		}

		inline void SetReturnValue(Type::atype_t* value)
		{
			value->isOnStack = true; //Protect it from gc
			if (returnValue)
				GetReturnValue();

			returnValue = value;
		}

		inline void Return()
		{
			int i = callstack.top();
			callstack.pop();
			pc = i;
		}

		std::vector<Bytecode> rom;
		Rom _rom;
		int pc;

		bool failed;

		void ExecuteInstruction(Bytecode& instruction);

		bool TryToLoadLib(const std::string& name);
		void PreloadFunctions();
		void PreloadLibraries();

	public:
		void Bind_Function(BindFunction& func);

		void Execute();

		void CallFunction(const char* funcName);
		void CallFunction(const char* funcName, const std::vector<Type::atype_t*>& params);

		inline void Fail() { failed = true; }
		inline bool Failed() const { return failed; }

		Interpreter(const Rom& rom) : rom(rom.GetRom()), _rom(rom), pc(0), failed(false)
		{
			instance = this;
			PreloadFunctions();
			PreloadLibraries();
		}

		~Interpreter();
	};
}

#pragma warning(pop)