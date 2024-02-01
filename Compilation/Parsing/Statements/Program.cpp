#include "Program.h"

void Astral::Program::Dump(int indent)
{
	std::cout << std::string(indent * 2, ' ') << "{ Program }\n";
	for (ParseTree* node : statements)
		node->Dump(indent + 1);
}

Astral::Program::~Program()
{
	for (ParseTree* node : statements)
		delete node;
}