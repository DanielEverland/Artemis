#include "DoubleVector3.h"

using namespace Maths::Vectors;

const DoubleVector3 DoubleVector3::Zero = DoubleVector3(0.0, 0.0, 0.0);
const DoubleVector3 DoubleVector3::Up = DoubleVector3(0.0, 1.0, 0.0);
const DoubleVector3 DoubleVector3::Down = DoubleVector3(0.0, -1.0, 0.0);
const DoubleVector3 DoubleVector3::Right = DoubleVector3(1.0, 0.0, 0.0);
const DoubleVector3 DoubleVector3::Left = DoubleVector3(-1.0, 0.0, 0.0);
const DoubleVector3 DoubleVector3::Forward = DoubleVector3(0.0, 0.0, 1.0);
const DoubleVector3 DoubleVector3::Back = DoubleVector3(0.0, 0.0, -1.0);