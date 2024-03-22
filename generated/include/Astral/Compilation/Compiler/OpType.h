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
		POP,

		STRUCT_ACCESS,

		LIT_NUMBER,
		LIT_STRING,
		VARIABLE,
		VARIABLE_REF,
		LIT_VOID,
		ADD,
		SUB,
		MUL,
		DIV,
		UNARY_MINUS,
		POW,
		MOD,
		NOT,
		FACTORIAL,

		OR,
		AND,

		EQUALITY,
		NEQUALITY,

		GREATER,
		GREATER_EQUALS,

		LESS,
		LESS_EQUALS,

		//Statements
		ASSIGN_VOID,
		ASSIGN,
		UPDATE_VAR,
		UPDATE_REF,
		UPDATE_MEMBER,

		IF,
		IF_ELSE,
		SKIP_BLOCK,

		SCOPE_BEG,
		SCOPE_END,

		CALL,
		FUNC_BEG,
		FUNC_RET,
		FUNC_END,

		WHILE_BEG,
		WHILE_END,
		WHILE_COND,
		WHILE_BREAK,
		WHILE_CONTINUE,
	};

	inline ASTRAL const char* OpTypeToString(OpType type)
	{
		switch (type)
		{
			case OpType::NOP:
				return "NOP";
			case OpType::GC:
				return "GC";
			case OpType::STRUCT_ACCESS:
				return "STRUCT_MEMBER";
			case OpType::POP:
				return "POP";
			case OpType::LIT_NUMBER:
				return "NUMBER";
			case OpType::LIT_STRING:
				return "STRING";
			case OpType::VARIABLE:
				return "VAR";
			case OpType::VARIABLE_REF:
				return "VAR_REF";
			case OpType::LIT_VOID:
				return "VOID";
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
			case OpType::OR:
				return "OR";
			case OpType::AND:
				return "AND";
			case OpType::EQUALITY:
				return "EQU";
			case OpType::NEQUALITY:
				return "NEQ";
			case OpType::NOT:
				return "NOT";
			case OpType::ASSIGN:
				return "ASSIGN";
			case OpType::ASSIGN_VOID:
				return "ASSIGN_VOID";
			case OpType::UPDATE_VAR:
				return "UPD_VAR";
			case OpType::UPDATE_REF:
				return "UPD_REF";
			case OpType::UPDATE_MEMBER:
				return "UPD_MEMBER";
			case OpType::SCOPE_BEG:
				return "SCOPE_BEG";
			case OpType::SCOPE_END:
				return "SCOPE_END";
			case OpType::CALL:
				return "CALL";
			case OpType::FUNC_BEG:
				return "FUNC_BEG";
			case OpType::FUNC_END:
				return "FUNC_END";
			case OpType::FUNC_RET:
				return "FUNC_RET";
			case OpType::IF:
				return "IF";
			case OpType::IF_ELSE:
				return "IF_ELSE";
			case OpType::SKIP_BLOCK:
				return "SKIP_BLOCK";
			case OpType::WHILE_BEG:
				return "WHILE_BEG";
			case OpType::WHILE_END:
				return "WHILE_END";
			case OpType::WHILE_BREAK:
				return "WHILE_BREAK";
			case OpType::WHILE_CONTINUE:
				return "WHILE_CONT";
			case OpType::WHILE_COND:
				return "WHILE_COND";
			default:
				return "UNKNOWN";
		}
	}
}

#pragma warning(pop)