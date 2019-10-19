#pragma once

template<typename T, int rows, int columns>
struct MatrixBase
{
public:
	T Elements[rows, columns];

protected:
	inline MatrixBase() {}
};