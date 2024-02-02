#pragma once
#include "../../Astral.h"
#include "../Tokenisation/Lexeme.h"

typedef unsigned char uint8_t;

namespace Astral
{
	struct ASTRAL Bytecode
	{
		uint8_t op;
		Lexeme lexeme;
	};
}