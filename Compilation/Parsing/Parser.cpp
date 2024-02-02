#include "Parser.h"

Astral::Token Astral::Parser::Peek()
{
	if (IsEof())
		return Token();

	return tokens[pointer];
}

Astral::Token Astral::Parser::Previous()
{
	if (pointer == 0)
		return Token();

	return tokens[pointer - 1ull];
}

Astral::Token Astral::Parser::Advance()
{
	if (!IsEof())
		++pointer;

	return Previous();
}

Astral::Token Astral::Parser::Consume(TokenType type, const std::string& message)
{
	if (Check(type))
		return Advance();

	Astral::Error(message.c_str(), Peek());
	failed = true;
	return {};
}

bool Astral::Parser::Check(TokenType type)
{
	if (IsEof())
		return false;

	return Peek().GetType() == type;
}

bool Astral::Parser::Match(TokenType type)
{
	return Match(&type, 1); //Please work and don't cause problems
}

bool Astral::Parser::Match(TokenType* types, unsigned int count)
{
	for (unsigned int i = 0; i < count; ++i)
	{
		if (Check(types[i]))
		{
			Advance();
			return true;
		}
	}

	return false;
}

Astral::Expression* Astral::Parser::ParseExpression()
{
	return ParseEquality();
}

Astral::Expression* Astral::Parser::ParseEquality()
{
	Expression* expr = ParseComparison();

	TokenType types[2]
	{
		TokenType::EQUALS,
		TokenType::NOT_EQUALS,
	};
	while (Match(types, 2))
	{
		Token op = Previous();
		Expression* right = ParseComparison();
		
		Expression* temp = expr;
		expr = new BinaryOp(temp, op, right);
	}

	return expr;
}

Astral::Expression* Astral::Parser::ParseComparison()
{
	Expression* expr = ParseTerm();

	TokenType types[4]
	{
		TokenType::GREATER_THAN,
		TokenType::GREATER_THAN_EQUAL,
		TokenType::LESS_THAN,
		TokenType::LESS_THAN_EQUAL,
	};
	while (Match(types, 4))
	{
		Token op = Previous();
		Expression* right = ParseTerm();
		
		Expression* temp = expr;
		expr = new BinaryOp(temp, op, right);
	}

	return expr;
}

Astral::Expression* Astral::Parser::ParseTerm()
{
	Expression* expr = ParseFactor();

	TokenType types[2]
	{
		TokenType::PLUS,
		TokenType::MINUS,
	};
	while (Match(types, 2))
	{
		Token op = Previous();
		Expression* right = ParseFactor();

		Expression* temp = expr;
		expr = new BinaryOp(temp, op, right);
	}

	return expr;
}

Astral::Expression* Astral::Parser::ParseFactor()
{
	Expression* expr = ParsePower();

	TokenType types[3]
	{
		TokenType::DIVIDE,
		TokenType::ASTERISK,
		TokenType::MODULO,
	};
	while (Match(types, 3))
	{
		Token op = Previous();
		Expression* right = ParsePower();

		Expression* temp = expr;
		expr = new BinaryOp(temp, op, right);
	}

	return expr;
}

Astral::Expression* Astral::Parser::ParsePower()
{
	Expression* expr = ParseUnary();

	while (Match(TokenType::HAT))
	{
		Token op = Previous();
		Expression* right = ParseUnary();

		Expression* temp = expr;
		expr = new BinaryOp(temp, op, right);
	}

	return expr;
}

Astral::Expression* Astral::Parser::ParseUnary()
{
	TokenType types[2]
	{
		TokenType::NOT,
		TokenType::MINUS,
	};
	if (Match(types, 2))
	{
		Token op = Previous();
		Expression* expr = ParseUnary();
		return new UnaryOp(op, expr);
	}

	return ParseLiteral();
}

Astral::Expression* Astral::Parser::ParseLiteral()
{
	if (Match(TokenType::NUMBER))
	{
		float* data = new float(std::stof(Previous().GetLexeme().lexeme));
		return new Literal(data, Literal::LiteralType::NUMBER, Previous());
	}

	if (Match(TokenType::L_BRA))
	{
		Expression* expr = ParseExpression();
		Consume(TokenType::R_BRA, "Expected ')'");
		return new Grouping(expr, Previous());
	}

	if (Match(TokenType::KEYWORD))
	{
		if (Previous().GetLexeme().lexeme == "true" ||
			Previous().GetLexeme().lexeme == "false"
			)
		{
			bool* data;
			if (Previous().GetLexeme().lexeme == "true")
				data = new bool(true);
			else
				data = new bool(false);

			return new Literal(data, Literal::LiteralType::BOOLEAN, Previous());
		}
		else
		{
			Error("Keyword was unexpected. Expected value", Previous());
			failed = true;
			Advance();
			return nullptr;
		}
	}

	Error("Expected value", tokens[tokens.size() - 1ull]);
	failed = true;
	Advance();

	return nullptr;
}

void Astral::Parser::Parse()
{
	while (!IsEof())
	{
		tree.push_back(ParseExpression());
	}

	Program* program = new Program(tokens[0]);
	program->SetStatements(tree);
	tree.clear();
	tree.push_back(program);
}