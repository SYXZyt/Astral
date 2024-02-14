#include "Compiler.h"

void Astral::Compiler::GenerateLiteral(const Literal* literal)
{
	switch (literal->type)
	{
		case Literal::LiteralType::NUMBER:
		{
			Bytecode code;
			code.lexeme = literal->GetToken().GetLexeme();
			code.op = (uint8_t)OpType::LIT_NUMBER;
			rom.push_back(code);
			break;
		}
		case Literal::LiteralType::BOOLEAN:
		{
			Bytecode code;
			code.op = (uint8_t)OpType::LIT_NUMBER;
			code.lexeme.lexeme = *(bool*)literal->data ? "1" : "0";
			rom.push_back(code);
			break;
		}
		case Literal::LiteralType::STRING:
		{
			Bytecode code;
			code.lexeme = literal->GetToken().GetLexeme();
			code.op = (uint8_t)OpType::LIT_STRING;
			rom.push_back(code);
			break;
		}
		case Literal::LiteralType::IDENTIFER:
		{
			Bytecode code;
			code.lexeme = literal->GetToken().GetLexeme();
			code.op = (uint8_t)OpType::VARIABLE;
			rom.push_back(code);
			break;
		}
		case Literal::LiteralType::REFERENCE:
		{
			Bytecode code;
			code.lexeme = literal->GetToken().GetLexeme();
			code.op = (uint8_t)OpType::VARIABLE_REF;
			rom.push_back(code);
			break;
		}
		default:
			throw "oop";
	}
}

void Astral::Compiler::GenerateUnary(const UnaryOp* unaryOp)
{
	GenerateExpression(unaryOp->GetExpression());

	OpType type;
	switch (unaryOp->GetToken().GetType())
	{
		case TokenType::MINUS:
			type = OpType::UNARY_MINUS;
			break;
		case TokenType::NOT:
			type = OpType::NOT;
			break;
		default:
			throw "Oop";
	}

	Bytecode code;
	code.op = (uint8_t)type;
	code.lexeme = unaryOp->GetToken().GetLexeme();
	rom.push_back(code);
}

void Astral::Compiler::GenerateBinary(const BinaryOp* binaryOp)
{
	GenerateExpression(binaryOp->Lhs());
	GenerateExpression(binaryOp->Rhs());

	OpType type;
	switch (binaryOp->GetToken().GetType())
	{
		case TokenType::PLUS:
			type = OpType::ADD;
			break;
		case TokenType::MINUS:
			type = OpType::SUB;
			break;
		case TokenType::ASTERISK:
			type = OpType::MUL;
			break;
		case TokenType::DIVIDE:
			type = OpType::DIV;
			break;
		case TokenType::HAT:
			type = OpType::POW;
			break;
		case TokenType::MODULO:
			type = OpType::MOD;
			break;
		case TokenType::EQUALS:
			type = OpType::EQUALITY;
			break;
		case TokenType::NOT_EQUALS:
			type = OpType::NEQUALITY;
			break;
		case TokenType::GREATER_THAN:
			type = OpType::GREATER;
			break;
		case TokenType::GREATER_THAN_EQUAL:
			type = OpType::GREATER_EQUALS;
			break;
		case TokenType::LESS_THAN:
			type = OpType::LESS;
			break;
		case TokenType::LESS_THAN_EQUAL:
			type = OpType::LESS_EQUALS;
			break;
		default:
			throw "Oop";
	}

	Bytecode code;
	code.lexeme = binaryOp->GetToken().GetLexeme();
	code.op = (uint8_t)type;
	rom.push_back(code);
}

void Astral::Compiler::GenerateExpression(const Expression* expression)
{
	if (const Grouping* grouping = dynamic_cast<const Grouping*>(expression))
		GenerateGrouping(grouping);
	else if (const Literal* literal = dynamic_cast<const Literal*>(expression))
		GenerateLiteral(literal);
	else if (const BinaryOp* binary = dynamic_cast<const BinaryOp*>(expression))
		GenerateBinary(binary);
	else if (const UnaryOp* unary = dynamic_cast<const UnaryOp*>(expression))
		GenerateUnary(unary);
	else if (const Factorial* factorial = dynamic_cast<const Factorial*>(expression))
		GenerateFactorial(factorial);
	else if (const IncrementExpression* increment = dynamic_cast<const IncrementExpression*>(expression))
		GenerateIncrementExpression(increment);
	else if (const DecrementExpression* decrement = dynamic_cast<const DecrementExpression*>(expression))
		GenerateDecrementExpression(decrement);
	else
	{
		throw "oop";
	}
}

void Astral::Compiler::GenerateGrouping(const Grouping* grouping)
{
	GenerateExpression(grouping->GetExpression());
}

void Astral::Compiler::GenerateNode(const ParseTree* node)
{
	if (const Expression* expr = dynamic_cast<const Expression*>(node))
		GenerateExpression(expr);
	else if (const Statement* stmt = dynamic_cast<const Statement*>(node))
		GenerateStatement(stmt);
	else
		throw "oop";
}

void Astral::Compiler::GenerateFactorial(const Factorial* factorial)
{
	GenerateExpression(factorial->GetExpression());

	Bytecode code;
	code.lexeme = factorial->GetToken().GetLexeme();
	code.op = (uint8_t)OpType::FACTORIAL;
	rom.push_back(code);
}

void Astral::Compiler::GenerateIncrementExpression(const IncrementExpression* increment)
{
	//If it is prefix (++x) we need to increment first, otherwise postfix (x++) we need to increment after
	if (increment->IsPrefix())
	{
		if (
			dynamic_cast<const IncrementExpression*>(increment->GetExpression()) ||
			dynamic_cast<const DecrementExpression*>(increment->GetExpression())
			)
		{
			Error("Cannot nest increment operator", increment->GetExpression()->GetToken());
			failed = true;
			return;
		}

		Lexeme lexeme = increment->GetToken().GetLexeme();
		lexeme.lexeme = "1";

		Bytecode code;
		code.lexeme = increment->GetExpression()->GetToken().GetLexeme();
		code.op = (uint8_t)OpType::VARIABLE;
		rom.push_back(code);

		code.lexeme = lexeme;
		code.op = (uint8_t)OpType::LIT_NUMBER;

		rom.push_back(code);

		code.op = (uint8_t)OpType::ADD;
		rom.push_back(code);

		code.lexeme = increment->GetExpression()->GetToken().GetLexeme();
		code.op = (uint8_t)OpType::UPDATE_VAR;
		rom.push_back(code);

		GenerateExpression(increment->GetExpression());
	}
	else
	{
		GenerateExpression(increment->GetExpression());

		Bytecode code;
		code.lexeme = increment->GetExpression()->GetToken().GetLexeme();
		code.op = (uint8_t)OpType::VARIABLE;

		rom.push_back(code);

		Lexeme lexeme = increment->GetToken().GetLexeme();
		lexeme.lexeme = "1";

		code.lexeme = lexeme;
		code.op = (uint8_t)OpType::LIT_NUMBER;
		rom.push_back(code);

		code.op = (uint8_t)OpType::ADD;
		rom.push_back(code);

		code.lexeme = increment->GetExpression()->GetToken().GetLexeme();
		code.op = (uint8_t)OpType::UPDATE_VAR;
		rom.push_back(code);
	}
}

void Astral::Compiler::GenerateDecrementExpression(const DecrementExpression* decrement)
{
	//If it is prefix (--x) we need to decrement first, otherwise postfix (x--) we need to decrement after
	if (decrement->IsPrefix())
	{
		if (
			dynamic_cast<const IncrementExpression*>(decrement->GetExpression()) ||
			dynamic_cast<const DecrementExpression*>(decrement->GetExpression())
			)
		{
			Error("Cannot nest decrement operator", decrement->GetExpression()->GetToken());
			failed = true;
			return;
		}

		Lexeme lexeme = decrement->GetToken().GetLexeme();
		lexeme.lexeme = "1";

		Bytecode code;
		code.lexeme = decrement->GetExpression()->GetToken().GetLexeme();
		code.op = (uint8_t)OpType::VARIABLE;
		rom.push_back(code);

		code.lexeme = lexeme;
		code.op = (uint8_t)OpType::LIT_NUMBER;

		rom.push_back(code);

		code.op = (uint8_t)OpType::SUB;
		rom.push_back(code);

		code.lexeme = decrement->GetExpression()->GetToken().GetLexeme();
		code.op = (uint8_t)OpType::UPDATE_VAR;
		rom.push_back(code);

		GenerateExpression(decrement->GetExpression());
	}
	else
	{
		GenerateExpression(decrement->GetExpression());

		Bytecode code;
		code.lexeme = decrement->GetExpression()->GetToken().GetLexeme();
		code.op = (uint8_t)OpType::VARIABLE;

		rom.push_back(code);

		Lexeme lexeme = decrement->GetToken().GetLexeme();
		lexeme.lexeme = "1";

		code.lexeme = lexeme;
		code.op = (uint8_t)OpType::LIT_NUMBER;
		rom.push_back(code);

		code.op = (uint8_t)OpType::SUB;
		rom.push_back(code);

		code.lexeme = decrement->GetExpression()->GetToken().GetLexeme();
		code.op = (uint8_t)OpType::UPDATE_VAR;
		rom.push_back(code);
	}
}

void Astral::Compiler::GenerateStatement(const Statement* statement)
{
	if (const Program* program = dynamic_cast<const Program*>(statement))
		GenerateProgram(program);
	else if (const PrintStatement* print = dynamic_cast<const PrintStatement*>(statement))
		GeneratePrint(print);
	else if (const VariableDefinition* var = dynamic_cast<const VariableDefinition*>(statement))
		GenerateLet(var);
	else if (const VariableAssignment* assign = dynamic_cast<const VariableAssignment*>(statement))
		GenerateAssign(assign);
	else if (const Block* block = dynamic_cast<const Block*>(statement))
		GenerateBlock(block);
	else if (const IfStatement* ifStatement = dynamic_cast<const IfStatement*>(statement))
		GenerateIf(ifStatement);
	else
		throw "oop";
}

void Astral::Compiler::GenerateProgram(const Program* program)
{
	for (ParseTree* node : program->Statements())
		GenerateNode(node);
}

void Astral::Compiler::GeneratePrint(const PrintStatement* printStatement)
{
	GenerateExpression(printStatement->Expr());

	Bytecode code;
	code.lexeme = printStatement->GetToken().GetLexeme();
	code.op = (uint8_t)OpType::PRINT;
	rom.push_back(code);
}

void Astral::Compiler::GenerateLet(const VariableDefinition* variable)
{
	//If the expression is non-null, we need to compile that since we have to assign to its result on the stack
	OpType assignType = OpType::ASSIGN_VOID;
	if (variable->Expr())
	{
		GenerateExpression(variable->Expr());
		assignType = OpType::ASSIGN;
	}

	Bytecode code;
	code.lexeme = variable->Name().GetLexeme();
	code.op = (uint8_t)assignType;
	rom.push_back(code);
}

void Astral::Compiler::GenerateAssign(const VariableAssignment* variable)
{
	GenerateExpression(variable->Expr());

	Bytecode code;
	code.lexeme = variable->GetToken().GetLexeme();
	code.op = (uint8_t)OpType::UPDATE_VAR;
	rom.push_back(code);
}

void Astral::Compiler::GenerateBlock(const Block* block)
{
	Bytecode scopeBegin;
	scopeBegin.lexeme = block->GetToken().GetLexeme();
	scopeBegin.op = (uint8_t)OpType::SCOPE_BEG;
	rom.push_back(scopeBegin);

	for (Statement* stmt : block->Statements())
		GenerateStatement(stmt);

	Bytecode scopeEnd;
	scopeEnd.lexeme = block->GetToken().GetLexeme();
	scopeEnd.op = (uint8_t)OpType::SCOPE_END;
	rom.push_back(scopeEnd);
}

void Astral::Compiler::GenerateIf(const IfStatement* ifStatement)
{
	GenerateExpression(ifStatement->IfExpression());

	Bytecode code;
	code.lexeme = ifStatement->GetToken().GetLexeme();
	code.op = (uint8_t)OpType::IF;

	//If we have an else block, we need a different operation as it needs to handle skipping the else block
	if (ifStatement->ElseBlock())
		code.op = (uint8_t)OpType::IF_ELSE;

	rom.push_back(code);

	BeginBlock(ifStatement->GetToken());
	GenerateStatement(ifStatement->IfBlock());
	EndBlock(ifStatement->GetToken());

	if (ifStatement->ElseBlock())
	{
		Bytecode skip;
		skip.lexeme = ifStatement->GetToken().GetLexeme();
		skip.op = (uint8_t)OpType::SKIP_BLOCK;
		rom.push_back(skip);

		BeginBlock(ifStatement->GetToken());
		GenerateStatement(ifStatement->ElseBlock());
		EndBlock(ifStatement->GetToken());
	}
}

void Astral::Compiler::GenerateBytecode()
{
	for (ParseTree* node : tree)
		GenerateNode(node);
}