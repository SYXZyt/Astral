#pragma once
#pragma warning(push)
#pragma warning(disable : 4251)

#include <string>
#include <vector>

#include "../Astral.h"
#include "BindFunction.h"

class Interpreter;

namespace Astral
{
	class ASTRAL Library final
	{
	private:
		std::string name;
		std::vector<BindFunction> functions;

	public:
		inline const std::string& Name() const { return name; }

		void AddFunction(const BindFunction& func);

		void Bind(Interpreter& interpreter);

		Library(const char* name) : name(name) {}
	};
}

#pragma warning(pop)