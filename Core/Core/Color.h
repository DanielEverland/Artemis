#pragma once

#include<cstdint>

using std::uint8_t;

struct Color
{
	uint8_t R;
	uint8_t G;
	uint8_t B;
	uint8_t A;

	static Color Black;
	static Color White;
};