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
#include "Runtime/BindFunction.h"
#include "Runtime/BuiltInFunctions.h"

namespace Astral::API
{
	typedef std::vector<ParseTree*> ast;

	ASTRAL bool CompileFile(const char* fname, Rom& generatedRom, bool dumpLexer = false, bool dumpParser = false, bool dumpRom = false);
	ASTRAL void RunInterpreter(Interpreter& interpreter);
	ASTRAL Interpreter CreateInterpreter(const Rom& rom);
	ASTRAL void ExecuteScript(const Rom& rom);
	ASTRAL void LoadDefaultLibraries();
	ASTRAL void MainCall(Interpreter& interpreter);
	ASTRAL bool CompileToParseTree(const char* fname, ast& tree, bool dumpLexer = false, bool dumpParser = false);
}