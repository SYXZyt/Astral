#include "Linker.h"

#include "../../API.h"

Astral::Linker* Astral::Linker::instance = nullptr;

std::vector<Astral::ParseTree*> Astral::Linker::ResolveInclude(const std::string& fname, bool& failed)
{
	if (HasBeenIncluded(fname))
	{
#if defined(_DEBUG) and defined(_WIN32)
		std::string out = "Linker prevented '" + std::filesystem::absolute(fname).string() + "' being included multiple times\n";
		OutputDebugStringA(out.c_str());
#endif
		return {};
	}

	AddFile(fname);

	Astral::API::ast tree;
	if (Astral::API::CompileToParseTree(fname.c_str(), tree, false, false))
	{
		failed = false;
		return tree;
	}

	failed = true;
	return {};
}