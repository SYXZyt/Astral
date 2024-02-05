#include "Variable.h"

void Astral::Variable::Dump(int indent)
{
	std::cout << std::string(indent * 2, ' ') << "{ Print }\n";
	expr->Dump(indent + 1);
}

Astral::Variable::~Variable()
{
	delete expr;
}