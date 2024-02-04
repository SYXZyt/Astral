#pragma once
#include "../../Astral.h"

typedef unsigned char uint8_t;

namespace Astral
{
	enum class ASTRAL OpType : uint8_t
	{
		NOP,
		LIT_NUMBER,
		LIT_STRING,
		ADD,
		SUB,
		MUL,
		DIV,
		UNARY_MINUS,
		POW,
		MOD,
		NOT,

		EQUALITY,
		NEQUALITY,

		GREATER,
		GREATER_EQUALS,

		LESS,
		LESS_EQUALS,

		//Statements
		PRINT,
	};

	inline ASTRAL const char* OpTypeToString(OpType type)
	{
		switch (type)
		{
			case OpType::NOP:
				return "NOP";
			case OpType::LIT_NUMBER:
				return "NUMBER";
			case OpType::LIT_STRING:
				return "STRING";
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
			case OpType::POW:
				return "POW";
			case OpType::MOD:
				return "MOD";
			case OpType::EQUALITY:
				return "EQU";
			case OpType::NEQUALITY:
				return "NEQ";
			case OpType::NOT:
				return "NOT";
			case OpType::PRINT:
				return "PRINT";
			default:
				return "UNKNOWN";
		}
	}
}