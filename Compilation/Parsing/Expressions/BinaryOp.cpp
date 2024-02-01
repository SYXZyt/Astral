#include "BinaryOp.h"

void Astral::BinaryOp::Dump(int indent)
{
	std::cout << std::string(indent * 2, ' ');
	std::cout << "{ Binary Op " << token.GetLexeme().lexeme << " }\n";
	lhs->Dump(indent + 1);
	rhs->Dump(indent + 1);
}

Astral::BinaryOp::~BinaryOp()
{
	delete lhs;
	delete rhs;
}