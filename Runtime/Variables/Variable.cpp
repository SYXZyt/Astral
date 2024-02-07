#include "Variable.h"

Astral::Variable::Variable(const char* name, std::shared_ptr<Type::atype_t> value)
{
	size_t len = strlen(name) + 1;
	varname = new char[len];
	strcpy_s(varname, len, name);
	varname[len - 1] = '\0';

	this->value = value;
}

Astral::Variable::~Variable()
{
	//delete value;
	delete[] varname;
}