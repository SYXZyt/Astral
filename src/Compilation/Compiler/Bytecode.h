#pragma once
#pragma warning(push)
#pragma warning(disable : 4251)

#include <cstring>
#include <ostream>
#include <sstream>
#include <iomanip>

#include "OpType.h"
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
#ifdef _WIN32
		if (strnlen_s(repr, 16) < 8)
#elif __linux__
        if (strlen(repr) < 8)
#endif
			os << '\t';

		std::stringstream ss;
		ss << std::hex << std::setw(2) << std::setfill('0') << (unsigned)bytecode.op << '\t';
		os << ss.str();
		os << bytecode.lexeme.lexeme;
		return os;
	}
}

#pragma warning(pop) 