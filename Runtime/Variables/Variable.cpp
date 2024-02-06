#include "Variable.h"

Astral::Variable::Variable(const char* name, Type::atype_t* value)
{
	size_t len = strlen(name) + 1;
	varname = new char[len];
	strcpy_s(varname, len, name);

	this->value = value;
}

Astral::Variable::~Variable()
{
	delete value;
	delete[] varname;
}