#pragma once
#pragma warning(push)
#pragma warning(disable : 4251)

#include <string>
#include <string.h>

#include "../../Astral.h"
#include "../BindFunction.h"

namespace Astral { struct MemoryBlock; }

namespace Astral::Type
{
	class ASTRAL atype_t
	{
	public:
		bool isOnStack = false; //Used in GC to determine whether this is OK to delete or not

		virtual atype_t* Copy() { return new atype_t(); }

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

		string_t();
		string_t(const char* value);
		string_t(const std::string& string);
		~string_t() final override;
	};

	class ASTRAL void_t final : public atype_t
	{
	public:
		atype_t* Copy() final override { return new void_t(); }
	};

	class ASTRAL ref_t final : public atype_t
	{
	private:
		MemoryBlock* block;

	public:
		MemoryBlock* GetBlock();

		atype_t* Copy() final override { return new ref_t(block); }

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

		func_t(size_t address, int paramCount) : address(address), paramCount(paramCount) {}
	};

	class ASTRAL externfunc_t final : public atype_t
	{
	private:
		BindFunction func;

	public:
		inline BindFunction& GetFunction() { return func; }

		atype_t* Copy() final override { return new externfunc_t(func); }

		externfunc_t(const BindFunction& func) : func(func) {}
	};
}

#pragma warning(pop)