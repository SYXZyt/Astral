#pragma once
typedef unsigned char uint8_t;

namespace Astral
{
	enum class OpType : uint8_t
	{
		NOP,
		LIT_NUMBER,
		ADD,
		SUB,
		MUL,
		DIV,
		UNARY_MINUS,
	};

	inline const char* OpTypeToString(OpType type)
	{
		switch (type)
		{
			case OpType::NOP:
				return "NOP";
			case OpType::LIT_NUMBER:
				return "NUMBER";
			case OpType::ADD:
				return "ADD";
			case OpType::SUB:
				return "SUB";
			case OpType::MUL:
				return "MUL";
			case OpType::DIV:
				return "DIV";
			case OpType::UNARY_MINUS:
				return "U_MIN";
			default:
				return "UNKNOWN";
		}
	}
}