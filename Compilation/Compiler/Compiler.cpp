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

void Astral::Compiler::GenerateStatement(const Statement* statement)
{
	if (const Program* program = dynamic_cast<const Program*>(statement))
		GenerateProgram(program);
	else
		throw "oop";
}

void Astral::Compiler::GenerateProgram(const Program* program)
{
	for (ParseTree* node : program->Statements())
		GenerateNode(node);
}

void Astral::Compiler::GenerateBytecode()
{
	for (ParseTree* node : tree)
		GenerateNode(node);
}