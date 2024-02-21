#include "FunctionCall.h"

void Astral::FunctionCall::Dump(int indent)
{
	std::cout << std::string(indent * 2, ' ') << "{ Function Call }\n";
	parameters->Dump(indent + 1);
}

Astral::FunctionCall::~FunctionCall()
{
	delete parameters;
}