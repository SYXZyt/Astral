#include "IfStatement.h"

void Astral::IfStatement::Dump(int indent)
{
	std::cout << std::string(indent * 2, ' ') << "{ If }\n";
	ifExpression->Dump(indent + 1);
	ifBlock->Dump(indent + 1);

	if (elseBlock)
	{
		std::cout << std::string(indent * 2, ' ') << "{ Else }\n";
		elseBlock->Dump(indent + 1);
	}
}

Astral::IfStatement::~IfStatement()
{
	delete ifExpression;
	delete ifBlock;
	delete elseBlock;
}