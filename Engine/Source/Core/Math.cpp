#include "Math.h"

const float Math::PI = 3.141592654f;

bool Math::IsPowerOfTwo(int value)
{
	return (value != 0) && ((value & (value - 1)) == 0);
}
