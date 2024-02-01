#include "Literal.h"

Astral::Literal::~Literal()
{
	if (data)
		delete data;
}