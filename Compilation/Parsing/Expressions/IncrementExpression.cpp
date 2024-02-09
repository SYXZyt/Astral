#include "IncrementExpression.h"

void Astral::IncrementExpression::Dump(int indent)
{
	std::cout << std::string(indent * 2, ' ');
	if (isPrefix)
		std::cout << "{ Prefix Increment Expression }\n";
	else
		std::cout << "{ Postfix Increment Expression }\n";

	expression->Dump(indent + 1);
}

Astral::IncrementExpression::~IncrementExpression()
{
	delete expression;
}