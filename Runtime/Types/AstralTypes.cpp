#include "AstralTypes.h"

Astral::Type::string_t::string_t()
{
	SetValue("");
}

Astral::Type::string_t::string_t(const char* value)
{
	SetValue(value);
}

Astral::Type::string_t::~string_t()
{
	FreeValue();
}