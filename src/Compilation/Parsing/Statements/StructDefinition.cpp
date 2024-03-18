#include "StructDefinition.h"

void Astral::StructDefinition::Dump(int indent)
{
	std::cout << std::string(indent * 2, ' ') << "{ Struct }\n";
	for (Token& member : members)
	{
		std::cout << std::string(indent + 1 * 2, ' ') << member.GetLexeme().lexeme << '\n';
	}
}