#pragma once
#pragma warning(push)
#pragma warning(disable : 4251)

#include <string>
#include <string.h>
#include <unordered_map>

#include "../../Astral.h"
#include "../BindFunction.h"

namespace Astral { struct MemoryBlock; 	class Variable; }

namespace Astral::Type
{
	class ASTRAL atype_t
	{
	public:
		bool isOnStack = false; //Used in GC to determine whether this is OK to delete or not

		virtual atype_t* Copy() { return new atype_t(); }
		virtual std::string ToString() const { return Type(); }
		virtual std::string Type() const { return "<ASTRAL::BASE>"; }

		virtual ~atype_t() {}
	};

	class ASTRAL number_t final : public atype_t
	{
	private:
		float value;

	public:
		inline float Value() const { return value; }
		inline void SetValue(float value) { this->value = value; }

		atype_t* Copy() final override { return new number_t(value); }
		std::string ToString() const final override { return std::to_string(value); }
		std::string Type() const final override { return "<ASTRAL::NUMBER>"; }

		number_t() : value(0.0f), atype_t() {}
		number_t(float v) : value(v), atype_t() {}
		~number_t() final override {}
	};

	class ASTRAL string_t final : public atype_t
	{
		//This class a little more complicated since we have to handle c-strings as we cannot export std::string
	private:
		char* value = nullptr;

		inline void FreeValue()
		{
			if (value)
				delete[] value;

			value = nullptr;
		}

	public:
		inline const char* Value() const { return value; }
		inline char* EditableValue() { return value; }

		inline void SetValue(const char* value)
		{
			size_t len = strlen(value);
			++len; //Allow space for null character

			FreeValue();

			this->value = new char[len];
			strcpy_s(this->value, len, value);
			this->value[len - 1] = '\0';
		}

		atype_t* Copy() final override
		{
			size_t len = strlen(value);
			++len;

			char* value = new char[len];
			strcpy_s(value, len, this->value);
			value[len - 1] = '\0';

			string_t* copy = new string_t(value);

			delete[] value;
			return copy;
		}

		std::string ToString() const final override { return value; }
		std::string Type() const final override { return "<ASTRAL::STRING>"; }

		string_t();
		string_t(const char* value);
		string_t(const std::string& string);
		~string_t() final override;
	};

	class ASTRAL void_t final : public atype_t
	{
	public:
		atype_t* Copy() final override { return new void_t(); }
		std::string ToString() const final override { return Type(); }
		std::string Type() const final override { return "<ASTRAL::VOID>"; }
	};

	class ASTRAL ref_t final : public atype_t
	{
	private:
		MemoryBlock* block;

	public:
		MemoryBlock* GetBlock();

		atype_t* Copy() final override { return new ref_t(block); }
		std::string ToString() const final override;
		std::string Type() const final override { return "<ASTRAL::REFERENCE>"; }

		ref_t(MemoryBlock* block) : block(block) {}
	};

	class ASTRAL func_t final : public atype_t
	{
	private:
		int paramCount;
		size_t address;

	public:
		inline int ParamCount() const { return paramCount; }
		inline size_t Address() const { return address; }

		atype_t* Copy() final override { return new func_t(address, paramCount); }
		std::string ToString() const final override { return Type(); }
		std::string Type() const final override { return "<ASTRAL::FUNC>"; }

		func_t(size_t address, int paramCount) : address(address), paramCount(paramCount) {}
	};

	class ASTRAL externfunc_t final : public atype_t
	{
	private:
		BindFunction func;

	public:
		inline BindFunction& GetFunction() { return func; }

		atype_t* Copy() final override { return new externfunc_t(func); }
		std::string ToString() const final override { return Type(); }
		std::string Type() const final override { return "<ASTRAL::EXTERN-FUNC>"; }

		externfunc_t(const BindFunction& func) : func(func) {}
	};

	class ASTRAL struct_t final : public atype_t
	{
	private:
		std::unordered_map<const char*, Type::atype_t*> members;

	public:
		atype_t* Copy() final override;
		std::string ToString() const final override { return Type(); }
		std::string Type() const final override { return "<ASTRAL::STRUCT>"; }

		void AddMember(const char* name, Variable* instance);

		atype_t** GetMember(const char* name);
		bool HasMember(const char* name) const;

		struct_t(const std::vector<const char*>& members);
	};
}

#pragma warning(pop)