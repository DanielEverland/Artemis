#include "FloatVector3.h"

ArtemisEngine::Math::FloatVector3::FloatVector3(int x, int y)
{
	this->x = float(x);
	this->y = float(y);
	this->z = 0;
}

ArtemisEngine::Math::FloatVector3::FloatVector3(int x, int y, int z)
{
	this->x = float(x);
	this->y = float(y);
	this->z = float(z);
}