#include "Astral.h"
#include "Runtime/Memory/GarbageCollector.h"

bool Astral::UseCLIOutput = true;

void Astral::SetGCLimit_Bytes(unsigned int byteThreshold)
{
	Astral::GarbageCollector::CullLimit = byteThreshold;
}

void Astral::SetGCLimit_Kilobytes(unsigned int kbThreshold)
{
	SetGCLimit_Bytes(kbThreshold * 1024);
}

void Astral::SetGCLimit_Megabytes(unsigned int mbThreshold)
{
	SetGCLimit_Kilobytes(mbThreshold * 1024);
}