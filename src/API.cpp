#include "API.h"

#include "Runtime/BuiltInLibraries.h"

inline std::string ReadFile(const char* fname, bool& good)
{
	std::ifstream in(fname);
	good = in.good();

	std::stringstream ss;
	ss << in.rdbuf();
	return ss.str();
}

bool Astral::API::CompileFile(const char* fname, Rom& generatedRom, bool dumpLexer, bool dumpParser, bool dumpRom)
{
	ast tree{};
	if (!CompileToParseTree(fname, tree, dumpLexer, dumpParser))
		return false;
	
	bool failed = false;
	Linker::Instance().AddFile(fname); //Does this really need to be a singleton?
	tree = Linker::Instance().SearchTree(tree, failed);
	Linker::FreeInstance();

	if (failed)
		return false;

	Compiler compiler(tree);
	compiler.GenerateBytecode();

	if (compiler.Failed())
		return false;

	generatedRom = compiler.GetRom();

	if (dumpRom)
	{
		for (const Astral::Bytecode& code : generatedRom.GetRom())
			std::cout << code << '\n';

		std::cout << '\n';
	}

	return true;
}

void Astral::API::RunInterpreter(Interpreter& interpreter)
{
	interpreter.Execute();
}

Astral::Interpreter Astral::API::CreateInterpreter(const Rom& rom)
{
	return Interpreter(rom);
}

void Astral::API::ExecuteScript(const Rom& rom)
{
	Interpreter interpreter = CreateInterpreter(rom);
	RunInterpreter(interpreter);
}

void Astral::API::LoadDefaultLibraries()
{
	Astral::LoadLibraries();
}

void Astral::API::MainCall(Interpreter& interpreter)
{
	interpreter.CallFunction("main");
}

bool Astral::API::CompileToParseTree(const char* fname, ast& tree, bool dumpLexer, bool dumpParser)
{
	bool good;
	std::string data = ReadFile(fname, good);

	if (!good)
	{
		Error((std::string("Failed to open file '") + fname + '\'').c_str());
		return false;
	}

	Lexer lexer(data, fname);
	lexer.Tokenise();
	if (lexer.Failed())
		return false;

	if (dumpLexer)
	{
		for (const Token& t : lexer.GetTokens())
			std::cout << t << '\n';

		std::cout << '\n';
	}

	Parser parser(lexer.GetTokens());
	parser.Parse();

	if (parser.HasFailed())
		return false;

	tree = parser.tree;

	if (dumpParser)
	{
		for (ParseTree* node : tree)
			node->Dump();
		std::cout << "\n\n";
	}

	return true;
}