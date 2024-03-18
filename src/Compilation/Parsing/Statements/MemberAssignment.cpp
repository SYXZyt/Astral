#include "MemberAssignment.h"

void Astral::MemberAssignment::Dump(int indent)
{
	std::cout << std::string(indent * 2, ' ') << "{ Member Assignment }\n";
	expr->Dump(indent + 1);
}

Astral::MemberAssignment::~MemberAssignment()
{
	delete va; //Will delete expr since this has ownership
	delete structMember;
}