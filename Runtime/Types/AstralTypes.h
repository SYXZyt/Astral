#pragma once
#include "../../Astral.h"
#include <string.h>

namespace Astral::Type
{
	class ASTRAL atype_t
	{
	public:
		virtual ~atype_t() {}
	};

	class ASTRAL number_t final : public atype_t
	{
	private:
		float value;

	public:
		inline float Value() const { return value; }
		inline void SetValue(float value) { this->value = value; }

		number_t() : value(0.0f), atype_t() {}
		number_t(float v) : value(v), atype_t() {}
		~number_t() final override {}
	};

	class ASTRAL string_t final : public atype_t
	{
		//This class a little more complicated since we have to handle c-strings as we cannot export std::string
	private:
		char* value;

		inline void FreeValue()
		{
			if (value)
				delete[] value;

			value = nullptr;
		}

	public:
		inline const char const* Value() const { return value; }

		inline void SetValue(const char* value)
		{
			size_t len = strlen(value);
			++len; //Allow space for null character

			FreeValue();

			this->value = new char[len];
			strcpy_s(this->value, len, value);
			this->value[len - 1] = '\0';
		}

		string_t();
		string_t(const char* value);
		~string_t() final override;
	};
}