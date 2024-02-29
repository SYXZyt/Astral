#include "DecrementExpression.h"

void Astral::DecrementExpression::Dump(int indent)
{
	std::cout << std::string(indent * 2, ' ');
	if (isPrefix)
		std::cout << "{ Prefix Decrement Expression }\n";
	else
		std::cout << "{ Postfix Decrement Expression }\n";

	expression->Dump(indent + 1);
}

Astral::DecrementExpression::~DecrementExpression()
{
	delete expression;
}