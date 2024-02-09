#include "Variable.h"

#include "../Memory/MemoryBlock.h"

void Astral::Variable::SetValue(Type::atype_t* value)
{
	GarbageCollector::Instance().RemoveDanglingPointer(value);
	delete this->value->data;
	this->value->data = value;
}

void Astral::Variable::SetValue(MemoryBlock* value)
{
	this->value->RemoveReference(this);
	this->value = value;
	this->value->referencing.push_back(this);
}

Astral::Variable::Variable(const char* name)
{
	size_t len = strlen(name) + 1;
	varname = new char[len];
	strcpy_s(varname, len, name);
	varname[len - 1] = '\0';

	value = GarbageCollector::Instance().New();
	value->referencing.push_back(this);
}

Astral::Variable::~Variable()
{
	delete[] varname;
	value->RemoveReference(this);
}