#pragma once
#pragma warning(push)
#pragma warning(disable : 4251)

#include <stack>
#include <array>
#include <string>
#include <vector>
#include <iostream>

#include "ParseTree.h"
#include "AllNodeTypes.h"

#include "../../Astral.h"
#include "../../ErrorManager.h"

namespace Astral
{
	class ASTRAL Parser final
	{
	private:
		std::vector<Token> tokens;
		int pointer;

		bool failed;

		std::stack<int> loopNest;

		void Error(const char* message, const Token& token);
		void Sync();
		Token Peek();
		Token Peek(int lookahead);
		Token Previous();
		Token Advance();
		Token Consume(TokenType type, const std::string& message);

		inline bool IsEof() const { return pointer >= tokens.size(); }

		bool Check(TokenType type);
		bool Match(TokenType type);
		bool Match(TokenType* types, size_t count);

		Expression* ParseExpression();
		Expression* ParseConditional();
		Expression* ParseEquality();
		Expression* ParseComparison();
		Expression* ParseTerm();
		Expression* ParseFactor();
		Expression* ParsePower();
		Expression* ParseUnary();
		Expression* ParsePrefix();
		Expression* ParseLiteral();
		Expression* ParseStructOffset(bool isTopLevel = false);
		Expression* ParseCallParams();

		Statement* ParseStatement();
		Statement* ParseDeclarations();
		Statement* ParseStructDecl();
		Statement* ParseBlock();
		Statement* ParseLetStatement();
		Statement* ParseAssignment();
		Statement* ParseIfStatement();
		Statement* ParseWhileStatement();
		Statement* ParseFunctionDefinition();
		Statement* ParseParamList();
		Statement* ParseReturn();
		Statement* ParseUsing();
		Statement* ParseInclude();
			
	public:
		inline bool HasFailed() const { return failed; }

		std::vector<ParseTree*> tree;

		void Parse();

		Parser(const std::vector<Token>& tokens) : tokens(tokens), pointer(0), failed(false) {}
	};
}

#pragma warning(pop)