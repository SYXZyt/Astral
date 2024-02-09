#include "VariableAssignment.h"

void Astral::VariableAssignment::Dump(int indent)
{
	std::cout << std::string(indent * 2, ' ') << "{ Variable Assignment }\n";
	expr->Dump(indent + 1);
}

Astral::VariableAssignment::~VariableAssignment()
{
	delete expr;
}