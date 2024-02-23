#pragma once
#pragma warning(push)
#pragma warning(disable : 4251)

#include <vector>

#include "../Astral.h"
#include "../Compilation/Tokenisation/Lexeme.h"

namespace Astral
{
	class Interpreter;

	namespace Type { class atype_t; }

	typedef const std::vector<Type::atype_t*>& FuncParams;

	class ASTRAL BindFunction
	{
	private:
		const char* fname;
		int paramCount;

		Type::atype_t* (*func)(const std::vector<Type::atype_t*>&, Interpreter&, const Lexeme&);

	public:
		inline const char* Name() const { return fname; }

		inline int ParamCount() const { return paramCount; }

		inline Type::atype_t* Call(const std::vector<Type::atype_t*>& params, Interpreter& vm, const Lexeme& caller)
		{
			return func(params, vm, caller);
		}

		void Bind(Interpreter& interpreter);

		BindFunction(const char* fname, int paramCount, Type::atype_t* (*func)(const std::vector<Type::atype_t*>&, Interpreter&, const Lexeme&)) :
			fname(fname),
			paramCount(paramCount),
			func(func) {}
	};
}

#pragma warning(pop)