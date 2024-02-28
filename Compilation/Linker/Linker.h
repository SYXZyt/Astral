#pragma once
#include <string>
#include <vector>
#include <filesystem>

#include "../../API.h"
#include "../Parsing/ParseTree.h"

namespace Astral
{
	class Linker final
	{
	private:
		std::vector<std::string> includedFiles;

		static Linker* instance;

	public:
		static Linker& GetInstance()
		{
			if (!instance)
				instance = new Linker();

			return *instance;
		}

		static void FreeInstance()
		{
			if (!instance)
				return;

			delete instance;
			instance = nullptr;
		}

		std::vector<ParseTree*> SearchTree(const std::vector<ParseTree*>& tree)
		{
			std::vector<ParseTree*> output;
			for (ParseTree* node : tree)
				output.push_back(node);

			for (ParseTree* node : tree)
			{
				if (const Include* include = dynamic_cast<const Include*>(node))
				{
					std::vector<ParseTree*> file = ResolveInclude(include->GetFileName().GetLexeme().lexeme);
					for (ParseTree* n : file)
						output.push_back(n);
				}
			}

			return output;
		}

		std::vector<ParseTree*> ResolveInclude(const std::string& fname)
		{
			if (HasBeenIncluded(fname))
				return {};

			includedFiles.push_back(fname);

			Astral::API::ast tree;
			Astral::API::CompileToParseTree(fname.c_str(), tree, false, false);
			return tree;
		}
			
		inline bool HasBeenIncluded(const std::string& fname) const { return std::count(includedFiles.begin(), includedFiles.end(), fname); }
	};
}