#pragma once
#include <string>
#include <unordered_map>

namespace Astral
{
	static const std::vector<std::string> Keywords
	{
		"true",
		"false",
	};

	inline bool IsKeyword(const std::string& iden)
	{
		return std::count(Keywords.begin(), Keywords.end(), iden) >= 1;
	}
}