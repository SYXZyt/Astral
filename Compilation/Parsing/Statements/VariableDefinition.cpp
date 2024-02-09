#include "VariableDefinition.h"

void Astral::VariableDefinition::Dump(int indent)
{
	std::cout << std::string(indent * 2, ' ') << "{ Variable Definition }\n";

	if (expr)
		expr->Dump(indent + 1);
}

Astral::VariableDefinition::~VariableDefinition()
{
	delete expr;
}