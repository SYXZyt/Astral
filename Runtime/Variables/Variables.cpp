#include "Variables.h"

bool Astral::Variables::DoesVariableExistInScope(const std::vector<Variable*>& scope, const char* vname)
{
	for (const Variable* v : scope)
	{
		if (strcmp(v->Name(), vname) == 0)
			return true;
	}

	return false;
}

Astral::Variable* Astral::Variables::GetVariable(const char* name)
{
	for (int i = variables.size() - 1; i >= 0; --i)
	{
		for (Variable* v : variables[i])
		{
			if (strcmp(v->Name(), name) == 0)
				return v;
		}
	}

	return nullptr;
}

bool Astral::Variables::DoesVariableExistInHighestScope(const char* name)
{
	return DoesVariableExistInScope(variables[variables.size() - 1], name);
}

bool Astral::Variables::DoesVariableExist(const char* name)
{
	//Loop in reverse since we want to start with the highest
	//scope which is at the end of the list
	for (int i = variables.size() - 1; i >= 0; --i)
	{
		if (DoesVariableExistInScope(variables[i], name))
			return true;
	}

	return false;
}

void Astral::Variables::AddVariable(const char* vname)
{
	Variable* v = new Variable(vname, new Type::void_t());
	variables[variables.size() - 1].push_back(v);
}

void Astral::Variables::UpdateValue(const char* vname, Type::atype_t* value)
{
	GetVariable(vname)->SetValue(value);
}

Astral::Type::atype_t* Astral::Variables::GetValue(const char* vname)
{
	return GetVariable(vname)->Value();
}

void Astral::Variables::AddScope()
{
	variables.push_back({});
}

void Astral::Variables::RemoveScope()
{
	//If we try to remove the global scope then something seriously has gone wrong.
	if (variables.size() <= 1)
		throw "Why are you trying to remove the global scope";

	for (Variable* v : variables[variables.size() - 1])
		delete v;

	variables.pop_back();
}

Astral::Variables::Variables()
{
	//Create the global scope
	AddScope();
}