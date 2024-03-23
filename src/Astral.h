#pragma once
#include <vector>

#ifdef _WIN32
#ifdef ASTRAL_EXPORT
    #define ASTRAL __declspec(dllexport)
  #else
    #define ASTRAL __declspec(dllimport)
  #endif
#elif __linux__
#define ASTRAL __attribute__((visibility("default")))
#endif

namespace Astral
{
	ASTRAL extern bool UseCLIOutput;
}