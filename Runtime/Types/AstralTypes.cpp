#include "AstralTypes.h"

Astral::Type::string_t::string_t()
{
	SetValue("");
}

Astral::Type::string_t::string_t(const char* value)
{
	SetValue(value);
}

Astral::Type::string_t::string_t(const std::string& string)
{
	SetValue(string.c_str());
}

Astral::Type::string_t::~string_t()
{
	FreeValue();
}