#pragma once
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
		os << OpTypeToString((OpType)bytecode.op) << '\t';
		std::stringstream ss;
		ss << std::hex << std::setw(2) << std::setfill('0') << (unsigned)bytecode.op << '\t';
		os << ss.str();
		os << bytecode.lexeme.lexeme;
		return os;
	}
}