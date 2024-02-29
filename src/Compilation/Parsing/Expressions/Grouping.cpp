#include "Grouping.h"

void Astral::Grouping::Dump(int indent)
{
	std::cout << std::string(indent * 2, ' ');
	std::cout << "{ Grouping }\n";

	if (expression)
		expression->Dump(indent + 1);
}

Astral::Grouping::~Grouping()
{
	delete expression;
}