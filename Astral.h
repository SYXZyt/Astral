#pragma once
#ifdef ASTRAL_EXPORT
#define ASTRAL __declspec(dllexport)
#else
#define ASTRAL __declspec(dllimport)
#endif