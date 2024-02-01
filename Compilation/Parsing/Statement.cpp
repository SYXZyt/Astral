#include "Statement.h"

void Astral::Statement::Dump(int indent)
{
	std::cout << std::string(indent * 2, ' ') << "{ Statement }\n";
}