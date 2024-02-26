#pragma once
#pragma warning(push)
#pragma warning(disable : 4251)

#include <vector>

#include "Bytecode.h"
#include "../../Astral.h"
#include "../../Runtime/Types/AstralTypes.h"

namespace Astral
{
	class ASTRAL Rom final
	{
	public:
		struct FunctionDefinition
		{
			Type::func_t* func;
			const char* name;
		};

	private:
		std::vector<Bytecode> rom;
		std::vector<Lexeme> usings;
		std::vector<FunctionDefinition> func;

	public:
		inline const std::vector<Bytecode>& GetRom() const { return rom; }
		inline const std::vector<FunctionDefinition>& GetFunction() const { return func; }
		inline const std::vector<Lexeme>& GetUsings() const { return usings; }

		inline void push_back(const Bytecode& instr) { rom.push_back(instr); }

		inline bool DoesFunctionExist(const char* name)
		{
			for (const FunctionDefinition& f : func)
				if (strcmp(name, f.name) == 0)
					return true;

			return false;
		}

		inline void AddUsing(const Lexeme& libName)
		{
			for (const Lexeme& lex : usings)
			{
				if (lex.lexeme == libName.lexeme)
					return;
			}

			usings.push_back(libName);
		}

		inline void AddFunction(const FunctionDefinition& function) { func.push_back(function); }

		inline void SetRom(const std::vector<Bytecode>& rom) { this->rom = rom; }

		Rom() = default;
	};
}

#pragma warning(pop)