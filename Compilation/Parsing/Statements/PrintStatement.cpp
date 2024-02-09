#include "PrintStatement.h"

void Astral::PrintStatement::Dump(int indent)
{
	std::cout << std::string(indent * 2, ' ') << "{ Print }\n";
	expr->Dump(indent + 1);
}

Astral::PrintStatement::~PrintStatement()
{
	delete expr;
}