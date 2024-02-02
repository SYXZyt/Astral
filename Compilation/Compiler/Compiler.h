#pragma once
#include <vector>
#include <string>
#include <sstream>

#include "OpType.h"
#include "Bytecode.h"
#include "../Parsing/ParseTree.h"

#include "../Parsing/AllNodeTypes.h"

namespace Astral
{
	class ASTRAL Compiler final
	{
	private:
		std::vector<Bytecode> rom;

		std::vector<ParseTree*> tree;

		bool failed = false;

		void GenerateLiteral(const Literal* literal);
		void GenerateUnary(const UnaryOp* unaryOp);
		void GenerateBinary(const BinaryOp* binaryOp);
		void GenerateExpression(const Expression* expression);
		void GenerateGrouping(const Grouping* grouping);
		void GenerateNode(const ParseTree* node);

		void GenerateStatement(const Statement* statement);
		void GenerateProgram(const Program* program);

	public:
		inline bool Failed() const { return failed; }
		
		const std::vector<Bytecode>& GetRom() const { return rom; }

		void GenerateBytecode();
		Compiler(const std::vector<ParseTree*>& tree) : tree(tree) {}
	};
}