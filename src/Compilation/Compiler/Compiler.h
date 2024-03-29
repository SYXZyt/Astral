#pragma once
#pragma warning(push)
#pragma warning(disable : 4251)

#include <vector>
#include <string>
#include <sstream>

#include "OpType.h"
#include "Rom.h"
#include "../../ErrorManager.h"
#include "../Parsing/ParseTree.h"

#include "../Parsing/AllNodeTypes.h"

namespace Astral
{
	class ASTRAL Compiler final
	{
	private:
		Rom rom;
		std::vector<Bytecode> buffer;

		std::vector<ParseTree*> tree;

		bool failed = false;

		inline void BeginBlock()
		{
			Bytecode code;
			code.lexeme = Lexeme();
			code.op = (uint8_t)OpType::SCOPE_BEG;
			rom.push_back(code);
		}

		inline void EndBlock()
		{
			Bytecode code;
			code.lexeme = Lexeme();
			code.op = (uint8_t)OpType::SCOPE_END;
			rom.push_back(code);
		}

		inline void GCPass()
		{
			Bytecode code;
			code.lexeme = Lexeme();
			code.op = (uint8_t)OpType::GC;
			rom.push_back(code);
		}

		void GenerateLiteral(const Literal* literal);
		void GenerateUnary(const UnaryOp* unaryOp);
		void GenerateBinary(const BinaryOp* binaryOp);
		void GenerateExpression(const Expression* expression);
		void GenerateGrouping(const Grouping* grouping);
		void GenerateNode(const ParseTree* node);
		void GenerateFactorial(const Factorial* factorial);
		void GenerateIncrementExpression(const IncrementExpression* increment);
		void GenerateDecrementExpression(const DecrementExpression* decrement);
		void GenerateCallParameters(const CallParameters* params);
		void GenerateFunctionCall(const FunctionCall* func);

		void GenerateStatement(const Statement* statement);
		void GenerateProgram(const Program* program);
		void GenerateLet(const VariableDefinition* variable);
		void GenerateAssign(const VariableAssignment* variable);
		void GenerateMemberAssign(const MemberAssignment* member);
		void GenerateBlock(const Block* block);
		void GenerateIf(const IfStatement* ifStatement);
		void GenerateWhile(const While* whileStatement);
		void GenerateContinue(const Continue* _continue);
		void GenerateBreak(const Break* _break);
		void GenerateFunctionDefinition(const Function* func);
		void GenerateStructDefinition(const StructDefinition* structDefinition);
		void GenerateFunctionParamList(const ParamList* params);
		void GenerateReturn(const Return* ret);
		void GenerateExpressionStatement(const ExpressionStatement* expr);
		void GenerateUsing(const Using* library);

		inline void GenerateStatementInsideBlock(const Statement* statement)
		{
			bool isBlockAlready = dynamic_cast<const Block*>(statement);

			//If this is already a block, we do not need to add one
			if (!isBlockAlready)
				BeginBlock();

			GenerateStatement(statement);

			if (!isBlockAlready)
				EndBlock();
		}

	public:
		inline bool Failed() const { return failed; }

		const Rom& GetRom() const { return rom; }

		void GenerateBytecode();
		Compiler(const std::vector<ParseTree*>& tree) : tree(tree) {}
	};
}
#pragma warning(pop)