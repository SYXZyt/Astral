#pragma once
#include <ostream>

#include "../../Astral.h"

namespace Astral
{
	enum class ASTRAL TokenType
	{
		_EOF,
		NUMBER,
		PLUS,
		MINUS,
		ASTERISK,
		DIVIDE,
		IDEN,
		STRING,
		L_BRA,
		R_BRA,
		L_CURLY,
		R_CURLY,
		SEMICOLON,
		COMMA,
		DOT,
		HAT,
		MODULO,

		NOT,
		LESS_THAN,
		GREATER_THAN,
		LESS_THAN_EQUAL,
		GREATER_THAN_EQUAL,

		ASSIGNMENT,
		EQUALS,
		NOT_EQUALS,

		//Keywords
		_TRUE,
		_FALSE,
		FUNC,
		LET,
		FOR,
		IF,
		ELSE,
		WHILE,
		RETURN,
	};

	ASTRAL inline std::ostream& operator<<(std::ostream& os, const TokenType& t)
	{
		switch (t)
		{
			case TokenType::NUMBER:
				os << "<NUMBER>";
				break;
			case TokenType::PLUS:
				os << "<PLUS>";
				break;
			case TokenType::MINUS:
				os << "<MINUS>";
				break;
			case TokenType::ASTERISK:
				os << "<ASTERISK>";
				break;
			case TokenType::DIVIDE:
				os << "DIVIDE";
				break;
			case TokenType::IDEN:
				os << "<IDENTIFIER>";
				break;
			case TokenType::STRING:
				os << "<STRING>";
				break;
			case TokenType::L_BRA:
				os << "<LEFT PARANTHESIS>";
				break;
			case TokenType::R_BRA:
				os << "<RIGHT PARENTHESIS>";
				break;
			case TokenType::L_CURLY:
				os << "<LEFT BRACE>";
				break;
			case TokenType::R_CURLY:
				os << "<RIGHT BRACE>";
				break;
			case TokenType::SEMICOLON:
				os << "<SEMICOLON>";
				break;

			case TokenType::COMMA:
				os << "<COMMA>";
				break;
			case TokenType::DOT:
				os << "<DOT>";
				break;
			case TokenType::NOT:
				os << "<NOT>";
				break;
			case TokenType::LESS_THAN:
				os << "<LESS THAN>";
				break;
			case TokenType::GREATER_THAN:
				os << "<GREATER THAN>";
				break;
			case TokenType::LESS_THAN_EQUAL:
				os << "<LESS THAN EQUALS>";
				break;
			case TokenType::GREATER_THAN_EQUAL:
				os << "<GREATER THAN EQUALS>";
				break;

			case TokenType::ASSIGNMENT:
				os << "<ASSIGNMENT>";
				break;
			case TokenType::EQUALS:
				os << "<EQUALS>";
				break;

			case TokenType::_TRUE:
				os << "<TRUE>";
				break;
			case TokenType::_FALSE:
				os << "<FALSE>";
				break;
			case TokenType::FUNC:
				os << "<FUNC>";
				break;
			case TokenType::LET:
				os << "<LET>";
				break;
			case TokenType::FOR:
				os << "<FOR>";
				break;
			case TokenType::IF:
				os << "<IF>";
				break;
			case TokenType::ELSE:
				os << "<ELSE>";
				break;
			case TokenType::WHILE:
				os << "<WHILE>";
				break;
			case TokenType::RETURN:
				os << "<RETURN>";
				break;

			default:
				os << "<UNKNOWN-TYPE>";
				break;
		}

		return os;
	}
}