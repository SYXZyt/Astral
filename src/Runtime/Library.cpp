#include "Library.h"
#include "Interpreter.h"

void Astral::Library::AddFunction(const BindFunction& func)
{
	//Check if the function has already been added
	for (const BindFunction& f : functions)
		if (strcmp(f.Name(), func.Name()) == 0)
			return;

	functions.push_back(func);
}

void Astral::Library::Bind(Interpreter& interpreter)
{
	for (BindFunction& func : functions)
		func.Bind(interpreter);
}