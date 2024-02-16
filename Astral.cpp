#include "Astral.h"
#include "Runtime/Memory/GarbageCollector.h"

bool Astral::UseCLIOutput = true;

void Astral::SetGCLimit_Bytes(unsigned int byteThreshold)
{
	SetGCLimit_Kilobytes(byteThreshold / 1024);
}

void Astral::SetGCLimit_Kilobytes(unsigned int kbThreshold)
{
	Astral::GarbageCollector::CullLimit = kbThreshold;
}

void Astral::SetGCLimit_Megabytes(unsigned int mbThreshold)
{
	SetGCLimit_Kilobytes(mbThreshold * 1024);
}