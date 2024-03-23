#pragma once
#include <vector>

#ifdef ASTRAL_EXPORT
#define ASTRAL __declspec(dllexport)
#else
#define ASTRAL __declspec(dllimport)
#endif

namespace Astral
{
	ASTRAL extern bool UseCLIOutput;
}