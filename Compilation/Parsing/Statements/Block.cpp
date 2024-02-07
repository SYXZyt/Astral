#include "Block.h"

void Astral::Block::Dump(int indent)
{
	std::cout << std::string(indent * 2, ' ') << "{ Block }\n";
	for (Statement* node : statements)
	{
		if (node)
			node->Dump(indent + 1);
	}
}

Astral::Block::~Block()
{
	for (Statement* node : statements)
		delete node;
}