#include "Math.h"

const double Math::Pi = M_PI;
const double Math::Infinity = std::numeric_limits<double>::infinity();
const double Math::NaN = nan("");

double Math::NormalizeAngle(double angle)
{	
	angle = Math::Remainder(angle, 360);

	// force it to be the positive remainder, so that 0 <= angle < 360  
	angle = Math::Remainder(angle + 360, 360);

	// force into the minimum absolute value residue class, so that -180 < angle <= 180
	if (angle > 180)
		angle -= 360;

	return angle;

}