#pragma once
#pragma warning(push)
#pragma warning(disable : 4251)

#include "../../Astral.h"

typedef unsigned char uint8_t;

namespace Astral
{
	enum class ASTRAL OpType : uint8_t
	{
		NOP,
		GC,

		LIT_NUMBER,
		LIT_STRING,
		VARIABLE,
		VARIABLE_REF,
		ADD,
		SUB,
		MUL,
		DIV,
		UNARY_MINUS,
		POW,
		MOD,
		NOT,
		FACTORIAL,

		EQUALITY,
		NEQUALITY,

		GREATER,
		GREATER_EQUALS,

		LESS,
		LESS_EQUALS,

		//Statements
		PRINT,
		ASSIGN_VOID,
		ASSIGN,
		UPDATE_VAR,
		UPDATE_REF,

		IF,
		IF_ELSE,
		SKIP_BLOCK,

		SCOPE_BEG,
		SCOPE_END,
	};

	inline ASTRAL const char* OpTypeToString(OpType type)
	{
		switch (type)
		{
			case OpType::NOP:
				return "NOP";
			case OpType::GC:
				return "GC";
			case OpType::LIT_NUMBER:
				return "NUMBER";
			case OpType::LIT_STRING:
				return "STRING";
			case OpType::VARIABLE:
				return "VAR";
			case OpType::VARIABLE_REF:
				return "VAR_REF";
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
			case OpType::FACTORIAL:
				return "FACTORIAL";
			case OpType::EQUALITY:
				return "EQU";
			case OpType::NEQUALITY:
				return "NEQ";
			case OpType::NOT:
				return "NOT";
			case OpType::PRINT:
				return "PRINT";
			case OpType::ASSIGN:
				return "ASSIGN";
			case OpType::ASSIGN_VOID:
				return "ASSIGN_VOID";
			case OpType::UPDATE_VAR:
				return "UPD_VAR";
			case OpType::UPDATE_REF:
				return "UPD_REF";
			case OpType::SCOPE_BEG:
				return "SCOPE_BEG";
			case OpType::SCOPE_END:
				return "SCOPE_END";
			case OpType::IF:
				return "IF";
			case OpType::IF_ELSE:
				return "IF_ELSE";
			case OpType::SKIP_BLOCK:
				return "SKIP_BLOCK";
			default:
				return "UNKNOWN";
		}
	}
}

#pragma warning(pop)