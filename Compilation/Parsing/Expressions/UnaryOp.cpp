#include "UnaryOp.h"

void Astral::UnaryOp::Dump(int indent)
{
	std::cout << std::string(indent * 2, ' ');
	std::cout << "{ Unary Op : " << op.GetLexeme().lexeme << " }\n";
	value->Dump(indent + 1);
}

Astral::UnaryOp::~UnaryOp()
{
	delete value;
}