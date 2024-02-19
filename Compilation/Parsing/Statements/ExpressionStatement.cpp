#include "ExpressionStatement.h"

void Astral::ExpressionStatement::Dump(int indent)
{
	std::cout << std::string(indent * 2, ' ') << "{ Expression Statement }\n";
	expr->Dump(indent + 1);
}

Astral::ExpressionStatement::~ExpressionStatement()
{
	delete expr;
}