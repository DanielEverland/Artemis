#include "DoubleVector3.h"

ArtemisEngine::Math::DoubleVector3::DoubleVector3(int x, int y)
{
	this->x = double(x);
	this->y = double(y);
	this->z = 0;
}

ArtemisEngine::Math::DoubleVector3::DoubleVector3(int x, int y, int z)
{
	this->x = double(x);
	this->y = double(y);
	this->z = double(z);
}