#pragma once
#pragma warning(push)
#pragma warning(disable : 4251)

#include <vector>

#include "../Astral.h"

namespace Astral
{
	class Interpreter;

	namespace Type { class atype_t; }

	class ASTRAL BindFunction
	{
	private:
		const char* fname;
		int paramCount;

		Type::atype_t* (*func)(const std::vector<Type::atype_t*>&);

	public:
		inline const char* Name() const { return fname; }

		inline int ParamCount() const { return paramCount; }

		inline Type::atype_t* Call(const std::vector<Type::atype_t*>& params)
		{
			return func(params);
		}

		void Bind(Interpreter& interpreter);

		BindFunction(const char* fname, int paramCount, Type::atype_t* (*func)(const std::vector<Type::atype_t*>&)) :
			fname(fname),
			paramCount(paramCount),
			func(func) {}
	};
}

#pragma warning(pop)