#include "Parser.h"

#define PreviousOrFirst() pointer >= tokens.size() ? tokens[0] : Previous()
#define PreviousOrLast() pointer >= tokens.size() ? tokens[tokens.size() - 1] : Previous()
#define PeekOrLast() pointer >= tokens.size() ? tokens[tokens.size() - 1] : Peek()

#define NULL_RET(expr)\
if (!expr)\
	return nullptr

void Astral::Parser::Error(const char* message, const Token& token)
{
	Astral::Error(message, token);
	Sync();
	failed = true;
}

void Astral::Parser::Sync()
{
	Advance();

	while (!IsEof())
	{
		if (Previous().GetType() == TokenType::SEMICOLON)
			return;

		switch (Previous().GetType())
		{
		case TokenType::FUNC:
		case TokenType::LET:
		case TokenType::FOR:
		case TokenType::IF:
		case TokenType::ELSE:
		case TokenType::WHILE:
		case TokenType::RETURN:
			return;
		}

		Advance();
	}
}

Astral::Token Astral::Parser::Peek()
{
	if (IsEof())
		return Token();

	return tokens[pointer];
}

Astral::Token Astral::Parser::Peek(int lookahead)
{
	if ((size_t)(pointer + lookahead) >= tokens.size())
		return Token();

	return tokens[(size_t)(pointer + lookahead)];
}

Astral::Token Astral::Parser::Previous()
{
	if (pointer == 0)
		return tokens[0];

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

	Error(message.c_str(), PreviousOrLast());
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

bool Astral::Parser::Match(TokenType* types, size_t count)
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
	return ParseConditional();
}

Astral::Expression* Astral::Parser::ParseConditional()
{
	Expression* expr = ParseEquality();
	NULL_RET(expr);

	std::array<TokenType, 2> types
	{
		TokenType::OR,
		TokenType::AND,
	};
	while (Match(types.data(), types.size()))
	{
		Token op = Previous();
		Expression* right = ParseEquality();
		NULL_RET(right);

		Expression* temp = expr;
		expr = new BinaryOp(temp, op, right);
	}

	return expr;
}

Astral::Expression* Astral::Parser::ParseEquality()
{
	Expression* expr = ParseComparison();
	NULL_RET(expr);

	std::array<TokenType, 2> types
	{
		TokenType::EQUALS,
		TokenType::NOT_EQUALS,
	};
	while (Match(types.data(), types.size()))
	{
		Token op = Previous();
		Expression* right = ParseComparison();
		NULL_RET(right);

		Expression* temp = expr;
		expr = new BinaryOp(temp, op, right);
	}

	return expr;
}

Astral::Expression* Astral::Parser::ParseComparison()
{
	Expression* expr = ParseTerm();
	NULL_RET(expr);

	std::array<TokenType, 4> types
	{
		TokenType::GREATER_THAN,
		TokenType::GREATER_THAN_EQUAL,
		TokenType::LESS_THAN,
		TokenType::LESS_THAN_EQUAL,
	};
	while (Match(types.data(), types.size()))
	{
		Token op = Previous();
		Expression* right = ParseTerm();
		NULL_RET(right);

		Expression* temp = expr;
		expr = new BinaryOp(temp, op, right);
	}

	return expr;
}

Astral::Expression* Astral::Parser::ParseTerm()
{
	Expression* expr = ParseFactor();
	NULL_RET(expr);

	std::array<TokenType, 2> types
	{
		TokenType::PLUS,
		TokenType::MINUS,
	};
	while (Match(types.data(), types.size()))
	{
		Token op = Previous();
		Expression* right = ParseFactor();
		NULL_RET(right);

		Expression* temp = expr;
		expr = new BinaryOp(temp, op, right);
	}

	return expr;
}

Astral::Expression* Astral::Parser::ParseFactor()
{
	Expression* expr = ParsePower();
	NULL_RET(expr);

	std::array<TokenType, 3> types
	{
		TokenType::DIVIDE,
		TokenType::ASTERISK,
		TokenType::MODULO,
	};
	while (Match(types.data(), types.size()))
	{
		Token op = Previous();
		Expression* right = ParsePower();
		NULL_RET(right);

		Expression* temp = expr;
		expr = new BinaryOp(temp, op, right);
	}

	return expr;
}

Astral::Expression* Astral::Parser::ParsePower()
{
	Expression* expr = ParseUnary();
	NULL_RET(expr);

	while (Match(TokenType::HAT))
	{
		Token op = Previous();
		Expression* right = ParseUnary();
		NULL_RET(right);

		Expression* temp = expr;
		expr = new BinaryOp(temp, op, right);
	}

	return expr;
}

Astral::Expression* Astral::Parser::ParseUnary()
{
	std::array<TokenType, 2> types
	{
		TokenType::NOT,
		TokenType::MINUS,
	};
	if (Match(types.data(), types.size()))
	{
		Token op = Previous();
		Expression* expr = ParseUnary();
		NULL_RET(expr);

		return new UnaryOp(op, expr);
	}

	return ParsePrefix();
}

Astral::Expression* Astral::Parser::ParsePrefix()
{
	if (Match(TokenType::INCREMENT))
	{
		Token token = Previous();
		if (Check(TokenType::IDEN))
		{
			Expression* variable = ParseLiteral();
			NULL_RET(variable);

			IncrementExpression* prefix = new IncrementExpression(variable, true, token);
			return prefix;
		}
		else
		{
			Error("Expected identifier", Peek());
			failed = true;
			return nullptr;
		}
	}
	else if (Match(TokenType::DECREMENT))
	{
		Token token = Previous();
		if (Check(TokenType::IDEN))
		{
			Expression* variable = ParseLiteral();
			NULL_RET(variable);

			DecrementExpression* prefix = new DecrementExpression(variable, true, token);
			return prefix;
		}
		else
		{
			Error("Expected identifier", Peek());
			failed = true;
			return nullptr;
		}
	}

	return ParseLiteral();
}

Astral::Expression* Astral::Parser::ParseLiteral()
{
	if (Match(TokenType::NUMBER))
	{
		float* data = new float(std::stof(Previous().GetLexeme().lexeme));
		Expression* value = new Literal(data, Literal::LiteralType::NUMBER, Previous());

		if (Peek().GetType() == TokenType::NOT)
		{
			Factorial* fact = new Factorial(value, Peek());
			Advance();
			return fact;
		}

		return value;
	}

	if (Match(TokenType::STRING))
	{
		std::string* data = new std::string(Previous().GetLexeme().lexeme);
		return new Literal(data, Literal::LiteralType::STRING, Previous());
	}

	if (Match(TokenType::IDEN))
	{
		std::string* data = new std::string(Previous().GetLexeme().lexeme);
		Expression* value = new Literal(data, Literal::LiteralType::IDENTIFER, Previous());

		if (Peek().GetType() == TokenType::NOT)
		{
			Factorial* fact = new Factorial(value, Peek());
			Advance();
			return fact;
		}
		else if (Peek().GetType() == TokenType::INCREMENT)
		{
			IncrementExpression* postfix = new IncrementExpression(value, false, Peek());
			Advance();
			return postfix;
		}
		else if (Peek().GetType() == TokenType::DECREMENT)
		{
			DecrementExpression* postfix = new DecrementExpression(value, false, Peek());
			Advance();
			return postfix;
		}

		//If the next token is a ( then we have a function call
		else if (Peek().GetType() == TokenType::L_BRA)
		{
			Token funcName = Previous();
			Advance();
			CallParameters* params = (CallParameters*)ParseCallParams();
			NULL_RET(params);

			return new FunctionCall(funcName, params);
		}

		return value;
	}

	if (Match(TokenType::REFERENCE))
	{
		//Make sure we are getting the reference of a variable
		Token varName = Consume(TokenType::IDEN, "Expected variable name");

		std::string* data = new std::string(Previous().GetLexeme().lexeme);
		return new Literal(data, Literal::LiteralType::REFERENCE, varName);
	}

	if (Match(TokenType::L_BRA))
	{
		Expression* expr = ParseExpression();
		NULL_RET(expr);

		Consume(TokenType::R_BRA, "Expected ')'");
		return new Grouping(expr, Previous());
	}

	TokenType booleans[2]
	{
		TokenType::_TRUE,
		TokenType::_FALSE,
	};
	if (Match(booleans, 2))
	{
		bool* data;
		if (Previous().GetType() == TokenType::_TRUE)
			data = new bool(true);
		else
			data = new bool(false);

		return new Literal(data, Literal::LiteralType::BOOLEAN, Previous());
	}

	Error("Expected expression", PeekOrLast());
	failed = true;

	return nullptr;
}

Astral::Expression* Astral::Parser::ParseCallParams()
{
	Token tok = Previous();

	std::vector<Expression*> parameters;

	if (tok.GetType() != TokenType::L_BRA)
	{
		Error("", tok);
		return nullptr;
	}

	//Do not parse params if the list is empty
	if (Peek().GetType() != TokenType::R_BRA)
	{
		while (true)
		{
			Expression* expr = ParseExpression();
			NULL_RET(expr);
			parameters.push_back(expr);

			//If the next token is a ) then we don't want to read the comma
			if (Peek().GetType() == TokenType::R_BRA)
				break;

			if (Consume(TokenType::COMMA, "Expected ','").GetType() == TokenType::_EOF)
				return nullptr;

			if (Previous().GetType() == TokenType::_EOF)
			{
				Error("End of file unexpected", Previous());
				return nullptr;
			}
		}
	}

	Consume(TokenType::R_BRA, "Expected ')'");

	return new CallParameters(tok, parameters);
}

Astral::Statement* Astral::Parser::ParseStatement()
{
	if (Match(TokenType::RETURN))
		return ParseReturn();

	if (Match(TokenType::LET))
		return ParseLetStatement();

	if (Match(TokenType::IDEN))
	{
		if (Peek().GetType() == TokenType::ASSIGNMENT || Peek().GetType() == TokenType::PLUS_EQUALS || Peek().GetType() == TokenType::MINUS_EQUALS)
			return ParseAssignment();
		else if (Peek().GetType() == TokenType::L_BRA)
		{
			Token func = Previous();
			Advance();

			CallParameters* params = (CallParameters*)ParseCallParams();
			NULL_RET(params);

			Consume(TokenType::SEMICOLON, "Expected ';'");

			return new ExpressionStatement(new FunctionCall(func, params));
		}
		else
		{
			Error("Expected statement", Previous());
		}
	}

	if (Match(TokenType::L_CURLY))
		return ParseBlock();

	if (Match(TokenType::IF))
		return ParseIfStatement();

	if (Match(TokenType::WHILE))
		return ParseWhileStatement();

	if (Match(TokenType::CONTINUE))
	{
		Continue* _continue = new Continue(Previous());
		if (loopNest.size() == 0 || loopNest.top() == 0)
		{
			Error("Continue can only be used inside of a loop", _continue->GetToken());
			return nullptr;
		}

		Consume(TokenType::SEMICOLON, "Expected ';'");

		return _continue;
	}

	if (Match(TokenType::BREAK))
	{
		Break* _break = new Break(Previous());

		if (loopNest.size() == 0 || loopNest.top() == 0)
		{
			Error("Break can only be used inside of a loop", _break->GetToken());
			return nullptr;
		}

		Consume(TokenType::SEMICOLON, "Expected ';'");

		return _break;
	}

	if (Match(TokenType::INCREMENT))
	{
		if (Peek().GetType() == TokenType::IDEN)
		{
			Token varName = Advance();
			Consume(TokenType::SEMICOLON, "Expected ';'");

			Lexeme lex = varName.GetLexeme();
			lex.lexeme = "1";

			Token temp;
			temp.SetLexeme(lex);
			temp.SetType(TokenType::NUMBER);

			Literal* numberOne = new Literal(new float(1.0), Literal::LiteralType::NUMBER, temp);
			Literal* variable = new Literal(new std::string(varName.GetLexeme().lexeme), Literal::LiteralType::IDENTIFER, varName);

			lex.lexeme = "+";
			temp.SetLexeme(lex);
			temp.SetType(TokenType::PLUS);

			BinaryOp* op = new BinaryOp(variable, temp, numberOne);
			return new VariableAssignment(varName, op);
		}
		else
		{
			Error("Expected identifier", Peek());
			failed = true;
			return nullptr;
		}
	}

	if (Match(TokenType::DECREMENT))
	{
		if (Peek().GetType() == TokenType::IDEN)
		{
			Token varName = Advance();
			Consume(TokenType::SEMICOLON, "Expected ';'");

			Lexeme lex = varName.GetLexeme();
			lex.lexeme = "1";

			Token temp;
			temp.SetLexeme(lex);
			temp.SetType(TokenType::NUMBER);

			Literal* numberOne = new Literal(new float(1.0), Literal::LiteralType::NUMBER, temp);
			Literal* variable = new Literal(new std::string(varName.GetLexeme().lexeme), Literal::LiteralType::IDENTIFER, varName);

			lex.lexeme = "-";
			temp.SetLexeme(lex);
			temp.SetType(TokenType::MINUS);

			BinaryOp* op = new BinaryOp(variable, temp, numberOne);
			return new VariableAssignment(varName, op);
		}
		else
		{
			Error("Expected identifier", Peek());
			failed = true;
			return nullptr;
		}
	}

	if (Match(TokenType::SEMICOLON))
	{
		return nullptr;
	}

	Error("Expected statement", PeekOrLast());
	failed = true;
	return nullptr;
}

Astral::Statement* Astral::Parser::ParseDeclarations()
{
	if (Match(TokenType::FUNC))
		return ParseFunctionDefinition();
	else
	{
		Error("Expected declaration", Peek());
		Sync();
		failed = true;
		return nullptr;
	}
}

Astral::Statement* Astral::Parser::ParseBlock()
{
	std::vector<Statement*> statements;

	Block* block = new Block(Previous());

	while (!Match(TokenType::R_CURLY))
	{
		Statement* stmt = ParseStatement();
		if (stmt)
			statements.push_back(stmt);

		if (IsEof())
		{
			Error("Expected '}'", PeekOrLast());
			failed = true;
			break;
		}
	}

	block->SetStatements(statements);
	return block;
}

Astral::Statement* Astral::Parser::ParseLetStatement()
{
	Token let = Previous();
	Token name = Consume(TokenType::IDEN, "Expected variable name");

	Expression* expr = nullptr;
	if (Match(TokenType::ASSIGNMENT))
	{
		expr = ParseExpression();
		NULL_RET(expr);
	}

	Consume(TokenType::SEMICOLON, "Expected ';'");
	return new VariableDefinition(let, name, expr);
}

Astral::Statement* Astral::Parser::ParseAssignment()
{
	Token name = Previous();

	Expression* expr;
	if (Match(TokenType::PLUS_EQUALS))
	{
		//Do some trickey here to turn += x into = ? + x
		expr = ParseExpression();
		NULL_RET(expr);

		if (expr)
		{
			Lexeme l = expr->GetToken().GetLexeme();
			l.lexeme = "+";

			BinaryOp* op = new BinaryOp(new Literal(new std::string(name.GetLexeme().lexeme), Literal::LiteralType::IDENTIFER, name), Token(l, TokenType::PLUS), expr);
			expr = op;
		}
	}
	else if (Match(TokenType::MINUS_EQUALS))
	{
		//Do some trickey here to turn -= x into = ? - x
		expr = ParseExpression();
		NULL_RET(expr);

		if (expr)
		{
			Lexeme l = expr->GetToken().GetLexeme();
			l.lexeme = "-";

			BinaryOp* op = new BinaryOp(new Literal(new std::string(name.GetLexeme().lexeme), Literal::LiteralType::IDENTIFER, name), Token(l, TokenType::MINUS), expr);
			expr = op;
		}
	}
	else if (Match(TokenType::INCREMENT))
	{
		//Just make this a += 1 statement
		Lexeme lex = Previous().GetLexeme();
		lex.lexeme = "1";
		Token tok;
		tok.SetLexeme(lex);
		tok.SetType(TokenType::NUMBER);

		expr = new Literal(new float(1), Literal::LiteralType::NUMBER, tok);

		lex.lexeme = "+";
		BinaryOp* op = new BinaryOp(new Literal(new std::string(name.GetLexeme().lexeme), Literal::LiteralType::IDENTIFER, name), Token(lex, TokenType::PLUS), expr);
		expr = op;
	}
	else if (Match(TokenType::DECREMENT))
	{
		//Just make this a += 1 statement
		Lexeme lex = Previous().GetLexeme();
		lex.lexeme = "1";
		Token tok;
		tok.SetLexeme(lex);
		tok.SetType(TokenType::NUMBER);

		expr = new Literal(new float(1), Literal::LiteralType::NUMBER, tok);

		lex.lexeme = "-";
		BinaryOp* op = new BinaryOp(new Literal(new std::string(name.GetLexeme().lexeme), Literal::LiteralType::IDENTIFER, name), Token(lex, TokenType::MINUS), expr);
		expr = op;
	}
	else
	{
		Consume(TokenType::ASSIGNMENT, "Expected '='");

		expr = ParseExpression();
		NULL_RET(expr);
	}

	Consume(TokenType::SEMICOLON, "Expected ';'");
	return new VariableAssignment(name, expr);
}

Astral::Statement* Astral::Parser::ParseIfStatement()
{
	Token _if = Previous();
	//Check that we have the (
	if (Peek().GetType() != TokenType::L_BRA)
	{
		Error("Expected '(' after if", Peek());
		return nullptr;
	}

	Expression* ifExpression = ParseExpression();
	NULL_RET(ifExpression);

	Statement* ifBlock = ParseStatement();
	NULL_RET(ifBlock);

	Statement* elseBlock = nullptr;

	//Now check if we have an else branch. It is optional so do not throw if it is missing
	if (Peek().GetType() == TokenType::ELSE)
	{
		Advance();
		elseBlock = ParseStatement();
		NULL_RET(elseBlock);
	}

	return new IfStatement(_if, ifExpression, ifBlock, elseBlock);
}

Astral::Statement* Astral::Parser::ParseWhileStatement()
{
	Token _while = Previous();

	++loopNest.top();

	//Ensure that we have the (
	if (Peek().GetType() != TokenType::L_BRA)
	{
		Error("Expected '(' after while", Peek());
		return nullptr;
	}

	Expression* loopCondition = ParseExpression();
	NULL_RET(loopCondition);

	Statement* body = ParseStatement();
	NULL_RET(body);

	--loopNest.top();

	return new While(_while, loopCondition, body);
}

Astral::Statement* Astral::Parser::ParseFunctionDefinition()
{
	loopNest.push(0);

	Token tok = Previous();
	Token name = Consume(TokenType::IDEN, "Expected function name");
	
	//Check if the consume failed
	if (name.GetType() == TokenType::_EOF)
		return nullptr;

	Advance();
	ParamList* parameters = (ParamList*)ParseParamList();
	NULL_RET(parameters);

	if (Previous().GetType() != TokenType::L_CURLY)
	{
		Error("Function body must be a block", Previous());
		return nullptr;
	}

	Block* body = (Block*)ParseBlock();
	NULL_RET(body);

	loopNest.pop();

	return new Function(tok, name, parameters, body);
}

Astral::Statement* Astral::Parser::ParseParamList()
{
	Token tok = Previous();

	std::vector<Lexeme> parameters;

	if (tok.GetType() != TokenType::L_BRA)
	{
		Error("", tok);
		return nullptr;
	}

	//Do not parse params if the list is empty
	if (Peek().GetType() != TokenType::R_BRA)
	{
		Advance();

		while (true)
		{
			Token varName = Previous();

			//If we did not have an identifier then we have an issue
			if (varName.GetType() != TokenType::IDEN)
			{
				Error("Expected parameter name", Previous());
				return nullptr;
			}

			parameters.push_back(varName.GetLexeme());

			//If the next token is a ) then we don't want to read the comma
			if (Peek().GetType() == TokenType::R_BRA)
			{
				break;
			}

			if (Consume(TokenType::COMMA, "Expected ','").GetType() == TokenType::_EOF)
				return nullptr;

			if (Previous().GetType() == TokenType::_EOF)
			{
				Error("End of file unexpected", Previous());
				return nullptr;
			}
		}
	}

	Consume(TokenType::R_BRA, "Expected ')'");
	Advance();

	return new ParamList(tok, parameters);
}

Astral::Statement* Astral::Parser::ParseReturn()
{
	Token tok = Previous();

	//If the next token is not a semicolon then we need to get the return value
	Expression* returnValue = nullptr;
	if (Peek().GetType() != TokenType::SEMICOLON)
	{
		returnValue = ParseExpression();
		NULL_RET(returnValue);
	}

	Consume(TokenType::SEMICOLON, "Expected ';'");

	return new Return(tok, returnValue);
}

void Astral::Parser::Parse()
{
	loopNest.push(0);

	while (!IsEof())
	{
		Statement* stmt = ParseDeclarations();
		if (stmt)
			tree.push_back(stmt);
	}

	if (tokens.size() == 0)
		return;

	Program* program = new Program(tokens[0]);
	program->SetStatements(tree);
	tree.clear();
	tree.push_back(program);

}