#pragma once
#include <array>
#include <string>
#include <vector>
#include <iostream>

#include "ParseTree.h"
#include "AllNodeTypes.h"

#include "../Keyword.h"
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

		Token Peek();
		Token Previous();
		Token Advance();
		Token Consume(TokenType type, const std::string& message);

		inline bool IsEof() const { return pointer >= tokens.size(); }

		bool Check(TokenType type);
		bool Match(TokenType type);
		bool Match(TokenType* types, unsigned int count);

		Expression* ParseExpression();
		Expression* ParseEquality();
		Expression* ParseComparison();
		Expression* ParseTerm();
		Expression* ParseFactor();
		Expression* ParsePower();
		Expression* ParseUnary();
		Expression* ParseLiteral();

	public:
		inline bool HasFailed() const { return failed; }

		std::vector<ParseTree*> tree;

		void Parse();

		Parser(const std::vector<Token>& tokens) : tokens(tokens), pointer(0), failed(false) {}
	};
}