#include "CallParameters.h"

void Astral::CallParameters::Dump(int indent)
{
	std::cout << std::string(indent * 2, ' ') << "{ Call Parameters }\n";
	for (Expression* expr : params)
		expr->Dump(indent + 1);
}

Astral::CallParameters::~CallParameters()
{
	for (Expression* expr : params)
		delete expr;
}