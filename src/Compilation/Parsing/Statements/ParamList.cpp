#include "ParamList.h"

void Astral::ParamList::Dump(int indent)
{
	std::cout << std::string(indent * 2, ' ') << "{ Param List }\n";
	for (Lexeme& name : declarations)
	{
		std::cout << std::string(indent * 2, ' ') << "{ ";
		std::cout << name.lexeme << " }\n";
	}
}