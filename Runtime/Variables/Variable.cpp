#include "Variable.h"

#include "../Memory/MemoryBlock.h"

void Astral::Variable::SetValue(Type::atype_t* value)
{
	delete this->value->data;
	this->value->data = value;
}

void Astral::Variable::SetValue(MemoryBlock* value)
{
	this->value->RemoveReference(this);
	this->value = value;
}

Astral::Variable::Variable(const char* name, MemoryBlock* value)
{
	size_t len = strlen(name) + 1;
	varname = new char[len];
	strcpy_s(varname, len, name);
	varname[len - 1] = '\0';

	this->value = value;
}

Astral::Variable::~Variable()
{
	delete[] varname;
	value->RemoveReference(this);
}