#include "AstralTypes.h"

#include "../Memory/MemoryBlock.h"

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

Astral::MemoryBlock* Astral::Type::ref_t::GetBlock()
{
	return block;
}

std::string Astral::Type::ref_t::ToString() const
{
	return block->data->ToString();
}