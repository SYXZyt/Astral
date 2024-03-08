#pragma once
#include <string>
#include <vector>
#include <filesystem>

#include "../Parsing/AllNodeTypes.h"
#include "../Parsing/ParseTree.h"

namespace Astral
{
	class Linker final
	{
	private:
		std::vector<std::string> includedFiles;

		static Linker* instance;

	public:
		static Linker& Instance()
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

		void AddFile(const char* fname)
		{
			std::string name = std::filesystem::absolute(fname).string();
			if (!HasBeenIncluded(name))
				includedFiles.push_back(name);
		}

		void AddFile(const std::string& fname)
		{
			AddFile(fname.c_str());
		}

		std::vector<ParseTree*> SearchTree(const std::vector<ParseTree*>& tree, bool& failed)
		{
			std::vector<ParseTree*> output;
			for (ParseTree* node : tree)
				output.push_back(node);

			for (ParseTree* node : dynamic_cast<const Program*>(tree[0])->Statements())
			{
				if (const Include* include = dynamic_cast<const Include*>(node))
				{
					std::vector<ParseTree*> file = ResolveInclude(include->GetFileName().GetLexeme().lexeme, failed);
					if (file.size())
					{
						file = SearchTree(file, failed);
						for (ParseTree* n : file)
							output.push_back(n);
					}
				}
			}

			return output;
		}

		std::vector<ParseTree*> ResolveInclude(const std::string& fname, bool& failed);
			
		inline bool HasBeenIncluded(const std::string& fname) const
		{
			std::string path = std::filesystem::absolute(fname).string();
			return std::count(includedFiles.begin(), includedFiles.end(), path);
		}
	};
}