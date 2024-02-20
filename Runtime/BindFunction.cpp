#include "BindFunction.h"

#include "Interpreter.h"

void Astral::BindFunction::Bind(Interpreter& interpreter)
{
	interpreter.Bind_Function(*this);
}