#pragma once
#pragma warning(push)
#pragma warning(disable : 4251)

#include "../Statement.h"

namespace Astral
{
	class Include final : public Statement
	{
	private:
		Token fileName;

	public:
		inline const Token& GetFileName() const { return fileName; }

		void Dump(int indent = 0) final override;

		Include(const Token& token, const Token& fileName) : Statement(token), fileName(fileName) {}
	};
}

#pragma warning(pop)