#pragma once
#pragma warning(push)
#pragma warning(disable : 4251)

#include "../Statement.h"

namespace Astral
{
	class Using final : public Statement
	{
	private:
		Token libraryName;

	public:
		inline const Token& GetLibraryName() const { return libraryName; }

		void Dump(int indent = 0) final override;

		Using(const Token& token, const Token& libraryName) : Statement(token), libraryName(libraryName) {}
	};
}

#pragma warning(pop)