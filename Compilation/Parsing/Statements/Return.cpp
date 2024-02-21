#include "Return.h"

void Astral::Return::Dump(int indent)
{
	std::cout << std::string(indent * 2, ' ') << "{ Return }\n";
	if (returnValue)
		returnValue->Dump(indent + 1);
}

Astral::Return::~Return()
{
	delete returnValue;
}