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

Astral::Type::atype_t* Astral::Type::struct_t::Copy()
{
	return new void_t(); //Temp for now
}

#include "../Memory/GarbageCollector.h"
#include "../Variables/Variable.h"

void Astral::Type::struct_t::AddMember(const char* name, Variable* instance)
{
	members[name] = new void_t();
}

Astral::Type::atype_t** Astral::Type::struct_t::GetMember(const char* name)
{
	return &members[name];
}

bool Astral::Type::struct_t::HasMember(const char* name) const
{
	for (auto& kvp : members)
		if (kvp.first == name)
			return true;

	return false;
}

Astral::Type::struct_t::struct_t(const std::vector<const char*>& members)
{
	for (const char* member : members)
		this->members[member] = new void_t();
}