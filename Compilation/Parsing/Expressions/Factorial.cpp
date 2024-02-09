#include "Factorial.h"

void Astral::Factorial::Dump(int indent)
{
	std::cout << std::string(indent * 2, ' ');
	std::cout << "{ Factorial " << token.GetLexeme().lexeme << " }\n";
	expr->Dump(indent + 2);
}

Astral::Factorial::~Factorial()
{
	delete expr;
}