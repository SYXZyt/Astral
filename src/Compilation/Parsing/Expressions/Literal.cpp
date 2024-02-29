#include "Literal.h"

void Astral::Literal::Dump(int indent)
{
	std::cout << std::string(indent * 2, ' ');
	std::cout << "{ Literal Value " << token.GetLexeme().lexeme << " }\n";
}

Astral::Literal::~Literal()
{
	if (data)
		delete data;
}