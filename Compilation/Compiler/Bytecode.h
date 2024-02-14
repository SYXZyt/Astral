#pragma once
#pragma warning(push)
#pragma warning(disable : 4251)

#include <ostream>
#include <sstream>
#include <iomanip>

#include "../../Astral.h"
#include "../Tokenisation/Lexeme.h"

typedef unsigned char uint8_t;

namespace Astral
{
	struct ASTRAL Bytecode
	{
		uint8_t op = 0u;
		Lexeme lexeme;
	};

	inline ASTRAL std::ostream& operator<<(std::ostream& os, const Bytecode& bytecode)
	{
		const char* repr = OpTypeToString((OpType)bytecode.op);

		os << repr << "\t";
		if (strnlen_s(repr, 16) < 8)
			os << '\t';

		std::stringstream ss;
		ss << std::hex << std::setw(2) << std::setfill('0') << (unsigned)bytecode.op << '\t';
		os << ss.str();
		os << bytecode.lexeme.lexeme;
		return os;
	}
}

#pragma warning(pop) 