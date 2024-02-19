#pragma once
#include <vector>

#include "Astral.h"

#include "Compilation/Tokenisation/Lexer.h"
#include "Compilation/Tokenisation/Token.h"

#include "Compilation/Parsing/Parser.h"
#include "Compilation/Parsing/ParseTree.h"

#include "Compilation/Compiler/Rom.h"
#include "Compilation/Compiler/Compiler.h"

#include "Runtime/Interpreter.h"

namespace Astral::API
{
	typedef std::vector<ParseTree*> ast;

	ASTRAL bool CompileFile(const char* fname, Rom& generatedRom, bool dumpLexer = false, bool dumpParser = false, bool dumpRom = false);
	ASTRAL void ExecuteScript(const Rom& rom);
}