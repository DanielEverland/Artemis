#include "Math.h"

bool Math::IsPowerOfTwo(int value)
{
	return (value != 0) && ((value & (value - 1)) == 0);
}
