#pragma once
#include <vector>

#include "Library.h"
#include "../Astral.h"
#include "Interpreter.h"
#include "BuiltInFunctions.h"

namespace Astral
{
	extern std::vector<Library> libraries;

	extern void LoadLibraries();
}