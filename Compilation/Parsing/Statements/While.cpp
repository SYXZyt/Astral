#include "While.h"

void Astral::While::Dump(int indent)
{
	std::cout << std::string(indent * 2, ' ') << "{ While }\n";
	loopCondition->Dump(indent + 1);
	body->Dump(indent + 1);
}

Astral::While::~While()
{
	delete loopCondition;
	delete body;
}