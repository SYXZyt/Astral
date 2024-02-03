#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#include <Compilation/Tokenisation/Lexer.h>
#include <Compilation/Tokenisation/Token.h>

#include <Compilation/Parsing/Parser.h>
#include <Compilation/Parsing/ParseTree.h>

#include <Compilation/Compiler/Compiler.h>
#include <Compilation/Compiler/Bytecode.h>

#include <Runtime/Interpreter.h>

typedef std::vector<Astral::Bytecode> rom;
typedef std::vector<Astral::ParseTree*> ast;

std::string ReadDemoFile()
{
	std::ifstream in("demo.ast");
	std::stringstream ss;
	ss << in.rdbuf();
	return ss.str();
}

int main(int, char**)
{
	std::string data = ReadDemoFile();

	Astral::Lexer lexer(data, "<ASTRAL-IO>");
	lexer.Tokenise();
	if (lexer.Failed())
		return 1;

	Astral::Parser parser(lexer.GetTokens());
	parser.Parse();

	if (parser.HasFailed())
		return 1;

	ast tree = parser.tree;
	for (Astral::ParseTree* node : tree)
		node->Dump();
	std::cout << "\n\n";

	Astral::Compiler compiler(tree);
	compiler.GenerateBytecode();

	if (compiler.Failed())
		return 1;

	rom _rom = compiler.GetRom();

	for (const Astral::Bytecode& code : _rom)
		std::cout << code << '\n';

	std::cout << '\n';

	Astral::Interpreter interpreter(_rom);
	interpreter.Execute();

	return 0;
}