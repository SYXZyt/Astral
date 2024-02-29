#include "Include.h"

void Astral::Include::Dump(int indent)
{
	std::cout << std::string(indent * 2, ' ') << "{ Include }\n";
	std::cout << std::string((indent + 1) * 2, ' ') << "{ " << fileName.GetLexeme().lexeme << " }\n";
}