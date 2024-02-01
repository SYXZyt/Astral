#include "BinaryOp.h"

Astral::BinaryOp::~BinaryOp()
{
	delete lhs;
	delete rhs;
}