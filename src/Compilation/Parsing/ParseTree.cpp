#include "ParseTree.h"

void Astral::ParseTree::Dump(int indent)
{
	std::cout << std::string(indent * 2, ' ');
	std::cout << "{ Generic Node }\n";
}