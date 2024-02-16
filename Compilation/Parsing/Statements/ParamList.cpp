#include "ParamList.h"

void Astral::ParamList::Dump(int indent)
{
	std::cout << std::string(indent * 2, ' ') << "{ Param List }\n";
	for (Statement* node : declarations)
	{
		if (node)
			node->Dump(indent + 1);
	}
}

Astral::ParamList::~ParamList()
{
	for (Statement* node : declarations)
		delete node;
}