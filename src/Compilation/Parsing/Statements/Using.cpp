#include "Using.h"

void Astral::Using::Dump(int indent)
{
	std::cout << std::string(indent * 2, ' ') << "{ Using }\n";
	std::cout << std::string((indent + 1) * 2, ' ') << "{ " << libraryName.GetLexeme().lexeme << " }\n";
}