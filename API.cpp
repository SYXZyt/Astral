#include "API.h"

inline std::string ReadFile(const char* fname)
{
	std::ifstream in("demo.ast");
	std::stringstream ss;
	ss << in.rdbuf();
	return ss.str();
}

bool Astral::API::CompileFile(const char* fname, rom& generatedRom, bool dumpLexer, bool dumpParser, bool dumpRom)
{
	generatedRom = std::vector<Bytecode>();

	std::string data = ReadFile(fname);

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

	ast tree = parser.tree;

	if (dumpParser)
	{
		for (ParseTree* node : tree)
			node->Dump();
		std::cout << "\n\n";
	}

	Compiler compiler(tree);
	compiler.GenerateBytecode();

	if (compiler.Failed())
		return false;

	generatedRom = compiler.GetRom();

	if (dumpRom)
	{
		for (const Astral::Bytecode& code : generatedRom)
			std::cout << code << '\n';

		std::cout << '\n';
	}

	return true;
}

void Astral::API::ExecuteScript(const rom& rom)
{
	Interpreter interpreter(rom);
	interpreter.Execute();
}