#pragma once
#ifdef ASTRAL_EXPORT
#define ASTRAL __declspec(dllexport)
#else
#define ASTRAL __declspec(dllimport)
#endif

namespace Astral
{
	ASTRAL extern bool UseCLIOutput;

	ASTRAL extern void SetGCLimit_Bytes(unsigned int byteThreshold);
	ASTRAL extern void SetGCLimit_Kilobytes(unsigned int kbThreshold);
	ASTRAL extern void SetGCLimit_Megabytes(unsigned int mbThreshold);
}