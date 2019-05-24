#include "Color.h"

namespace ArtemisEngine
{
	Color::Color(BYTE red, BYTE green, BYTE blue)
	{
		r = red;
		g = green;
		b = blue;
	}
	Color::Color(BYTE red, BYTE green, BYTE blue, BYTE alpha)
	{
		r = red;
		g = green;
		b = blue;
		a = alpha;
	}

	Color Color::FromFloat(float red, float green, float blue)
	{
		return Color(BYTE(red * 0xFF), BYTE(green * 0xFF), BYTE(blue * 0xFF), 0xFF);
	}

	Color Color::FromFloat(float red, float green, float blue, float alpha)
	{
		return Color(BYTE(red * 0xFF), BYTE(green * 0xFF), BYTE(blue * 0xFF), BYTE(alpha * 0xFF));
	}

	const Color Color::AliceBlue(0xFF, 0xF0, 0xF8, 0xFF);
	const Color Color::AntiqueWhite(0xFF, 0xFA, 0xEB, 0xD7);
	const Color Color::Aqua(0xFF, 0x00, 0xFF, 0xFF);
	const Color Color::Aquamarine(0xFF, 0x7F, 0xFF, 0xD4);
	const Color Color::Azure(0xFF, 0xF0, 0xFF, 0xFF);
	const Color Color::Beige(0xFF, 0xF5, 0xF5, 0xDC);
	const Color Color::Bisque(0xFF, 0xFF, 0xE4, 0xC4);
	const Color Color::Black(0xFF, 0x00, 0x00, 0x00);
	const Color Color::BlanchedAlmond(0xFF, 0xFF, 0xEB, 0xCD);
	const Color Color::Blue(0xFF, 0x00, 0x00, 0xFF);
	const Color Color::BlueViolet(0xFF, 0x8A, 0x2B, 0xE2);
	const Color Color::Brown(0xFF, 0xA5, 0x2A, 0x2A);
	const Color Color::BurlyWood(0xFF, 0xDE, 0xB8, 0x87);
	const Color Color::CadetBlue(0xFF, 0x5F, 0x9E, 0xA0);
	const Color Color::Chartreuse(0xFF, 0x7F, 0xFF, 0x00);
	const Color Color::Chocolate(0xFF, 0xD2, 0x69, 0x1E);
	const Color Color::Coral(0xFF, 0xFF, 0x7F, 0x50);
	const Color Color::CornflowerBlue(0xFF, 0x64, 0x95, 0xED);
	const Color Color::Cornsilk(0xFF, 0xFF, 0xF8, 0xDC);
	const Color Color::Crimson(0xFF, 0xDC, 0x14, 0x3C);
	const Color Color::Cyan(0xFF, 0x00, 0xFF, 0xFF);
	const Color Color::DarkBlue(0xFF, 0x00, 0x00, 0x8B);
	const Color Color::DarkCyan(0xFF, 0x00, 0x8B, 0x8B);
	const Color Color::DarkGoldenrod(0xFF, 0xB8, 0x86, 0x0B);
	const Color Color::DarkGray(0xFF, 0xA9, 0xA9, 0xA9);
	const Color Color::DarkGreen(0xFF, 0xA9, 0xA9, 0xA9);
	const Color Color::DarkKhaki(0xFF, 0xBD, 0xB7, 0x6B);
	const Color Color::DarkMagenta(0xFF, 0x8B, 0x00, 0x8B);
	const Color Color::DarkOliveGreen(0xFF, 0x55, 0x6B, 0x2F);
	const Color Color::DarkOrange(0xFF, 0xFF, 0x8C, 0x00);
	const Color Color::DarkOrchid(0xFF, 0x99, 0x32, 0xCC);
	const Color Color::DarkRed(0xFF, 0x8B, 0x00, 0x00);
	const Color Color::DarkSalmon(0xFF, 0xE9, 0x96, 0x7A);
	const Color Color::DarkSeaGreen(0xFF, 0x8F, 0xBC, 0x8F);
	const Color Color::DarkSlateBlue(0xFF, 0x48, 0x3D, 0x8B);
	const Color Color::DarkSlateGray(0xFF, 0x2F, 0x4F, 0x4F);
	const Color Color::DarkTurquoise(0xFF, 0x00, 0xCE, 0xD1);
	const Color Color::DarkViolet(0xFF, 0x94, 0x00, 0xD3);
	const Color Color::DeepPink(0xFF, 0xFF, 0x14, 0x93);
	const Color Color::DeepSkyBlue(0xFF, 0x00, 0xBF, 0xFF);
	const Color Color::Denmark(0xD0, 0x0C, 0x33, 0xFF);
	const Color Color::DimGray(0xFF, 0x69, 0x69, 0x69);
	const Color Color::DodgerBlue(0xFF, 0x1E, 0x90, 0xFF);
	const Color Color::Firebrick(0xFF, 0xB2, 0x22, 0x22);
	const Color Color::FloralWhite(0xFF, 0xFF, 0xFA, 0xF0);
	const Color Color::ForestGreen(0xFF, 0x22, 0x8B, 0x22);
	const Color Color::Fuchsia(0xFF, 0xFF, 0x00, 0xFF);
	const Color Color::Gainsboro(0xFF, 0xDC, 0xDC, 0xDC);
	const Color Color::GhostWhite(0xFF, 0xF8, 0xF8, 0xFF);
	const Color Color::Gold(0xFF, 0xFF, 0xD7, 0x00);
	const Color Color::Goldenrod(0xFF, 0xDA, 0xA5, 0x20);
	const Color Color::Gray(0xFF, 0x80, 0x80, 0x80);
	const Color Color::Green(0xFF, 0x00, 0x80, 0x00);
	const Color Color::GreenYellow(0xFF, 0xAD, 0xFF, 0x2F);
	const Color Color::Honeydew(0xFF, 0xF0, 0xFF, 0xF0);
	const Color Color::HotPink(0xFF, 0xFF, 0x69, 0xB4);
	const Color Color::IndianRed(0xFF, 0xCD, 0x5C, 0x5C);
	const Color Color::Indigo(0xFF, 0x4B, 0x00, 0x82);
	const Color Color::Ivory(0xFF, 0xFF, 0xFF, 0xF0);
	const Color Color::Khaki(0xFF, 0xF0, 0xE6, 0x8C);
	const Color Color::Lavender(0xFF, 0xE6, 0xE6, 0xFA);
	const Color Color::LavenderBlush(0xFF, 0xFF, 0xF0, 0xF5);
	const Color Color::LawnGreen(0xFF, 0x7C, 0xDC, 0x00);
	const Color Color::LemonChiffon(0xFF, 0xFF, 0xFA, 0xCD);
	const Color Color::LightBlue(0xFF, 0xAD, 0xD8, 0xE6);
	const Color Color::LightCoral(0xFF, 0xF0, 0x80, 0x80);
	const Color Color::LightCyan(0xFF, 0xE0, 0xFF, 0xFF);
	const Color Color::LightGoldenrodYellow(0xFF, 0xFA, 0xFA, 0xD2);
	const Color Color::LightGray(0xFF, 0xD3, 0xD3, 0xD3);
	const Color Color::LightGreen(0xFF, 0x90, 0xEE, 0x90);
	const Color Color::LightPink(0xFF, 0xFF, 0xB6, 0xC1);
	const Color Color::LightSalmon(0xFF, 0xFF, 0xA0, 0x7A);
	const Color Color::LightSeaGreen(0xFF, 0x20, 0xB2, 0xAA);
	const Color Color::LightSkyBlue(0xFF, 0x87, 0xCE, 0xFA);
	const Color Color::LightSlateGray(0xFF, 0x77, 0x88, 0x99);
	const Color Color::LightSteelBlue(0xFF, 0xB0, 0xC4, 0xDE);
	const Color Color::LightYellow(0xFF, 0xFF, 0xFF, 0xE0);
	const Color Color::Lime(0xFF, 0x00, 0xFF, 0x00);
	const Color Color::LimeGreen(0xFF, 0x32, 0xCD, 0x32);
	const Color Color::Linen(0xFF, 0xFA, 0xF0, 0xE6);
	const Color Color::Magenta(0xFF, 0xFF, 0x00, 0xFF);
	const Color Color::Maroon(0xFF, 0x80, 0x00, 0x00);
	const Color Color::MediumAquamarine(0xFF, 0x66, 0xCD, 0xAA);
	const Color Color::MediumBlue(0xFF, 0x00, 0x00, 0xCD);
	const Color Color::MediumOrchid(0xFF, 0xBA, 0x55, 0xD3);
	const Color Color::MediumPurple(0xFF, 0x93, 0x70, 0xDB);
	const Color Color::MediumSeaGreen(0xFF, 0x3C, 0xB3, 0x71);
	const Color Color::MediumSlateBlue(0xFF, 0x7B, 0x68, 0xEE);
	const Color Color::MediumSpringGreen(0xFF, 0x00, 0xFA, 0x9A);
	const Color Color::MediumTurquoise(0xFF, 0x48, 0xD1, 0xCC);
	const Color Color::MediumVioletRed(0xFF, 0xC7, 0x15, 0x85);
	const Color Color::MidnightBlue(0xFF, 0x19, 0x19, 0x70);
	const Color Color::MintCream(0xFF, 0xF5, 0xFF, 0xFA);
	const Color Color::MistyRose(0xFF, 0xFF, 0xE4, 0xE1);
	const Color Color::Moccasin(0xFF, 0xFF, 0xE4, 0xB5);
	const Color Color::NavajoWhite(0xFF, 0xFF, 0xDE, 0xAD);
	const Color Color::Navy(0xFF, 0x00, 0x00, 0x80);
	const Color Color::OldLace(0xFF, 0xFD, 0xF5, 0xE6);
	const Color Color::Olive(0xFF, 0x80, 0x80, 0x00);
	const Color Color::OliveDrab(0xFF, 0x6B, 0x8E, 0x23);
	const Color Color::Orange(0xFF, 0xFF, 0xA5, 0x00);
	const Color Color::OrangeRed(0xFF, 0xFF, 0x45, 0x00);
	const Color Color::Orchid(0xFF, 0xDA, 0x70, 0xD6);
	const Color Color::PaleGoldenrod(0xFF, 0xEE, 0xE8, 0xAA);
	const Color Color::PaleGreen(0xFF, 0x98, 0xFB, 0x98);
	const Color Color::PaleTurquoise(0xFF, 0xAF, 0xEE, 0xEE);
	const Color Color::PapayaWhip(0xFF, 0xDB, 0x70, 0x93);
	const Color Color::PeachPuff(0xFF, 0xFF, 0xEF, 0xD5);
	const Color Color::Peru(0xFF, 0xFF, 0xDA, 0xB9);
	const Color Color::Pink(0xFF, 0xCD, 0x85, 0x3F);
	const Color Color::Plum(0xFF, 0xFF, 0xC0, 0xCB);
	const Color Color::PowderBlue(0xFF, 0xB0, 0xE0, 0xE6);
	const Color Color::Purple(0xFF, 0x80, 0x00, 0x80);
	const Color Color::Red(0xFF, 0xFF, 0x00, 0x00);
	const Color Color::RosyBrown(0xFF, 0xBC, 0x8F, 0x8F);
	const Color Color::RoyalBlue(0xFF, 0x41, 0x69, 0xE1);
	const Color Color::SaddleBrown(0xFF, 0x8B, 0x45, 0x13);
	const Color Color::Salmon(0xFF, 0xFA, 0x80, 0x72);
	const Color Color::SandyBrown(0xFF, 0xF4, 0xA4, 0x60);
	const Color Color::SeaGreen(0xFF, 0x2E, 0x8B, 0x57);
	const Color Color::SeaShell(0xFF, 0xFF, 0xF5, 0xEE);
	const Color Color::Sienna(0xFF, 0xA0, 0x52, 0x2D);
	const Color Color::Silver(0xFF, 0xC0, 0xC0, 0xC0);
	const Color Color::SkyBlue(0xFF, 0x87, 0xCE, 0xEB);
	const Color Color::SlateBlue(0xFf, 0x6A, 0x5A, 0xCD);
	const Color Color::SlateGray(0xFF, 0x70, 0x80, 0x90);
	const Color Color::Snow(0xFF, 0xFF, 0xFA, 0xFa);
	const Color Color::SpringGreen(0xFF, 0x00, 0xFF, 0x7F);
	const Color Color::SteelBlue(0xFF, 0x46, 0x82, 0xB4);
	const Color Color::Tan(0xFF, 0xD2, 0xB4, 0x8C);
	const Color Color::Teal(0xFF, 0x00, 0x80, 0x80);
	const Color Color::Thistle(0xFF, 0xD8, 0xBF, 0xD8);
	const Color Color::Tomato(0xFF, 0xFF, 0x63, 0x47);
	const Color Color::Transparent(0x00, 0x00, 0x00, 0x00);
	const Color Color::Turquoise(0xFF, 0x40, 0xE0, 0xD0);
	const Color Color::Violet(0xFF, 0xEE, 0x82, 0xEE);
	const Color Color::Wheat(0xFF, 0xF5, 0xDE, 0xB3);
	const Color Color::White(0xFF, 0xFF, 0xFF, 0xFF);
	const Color Color::WhiteSmoke(0xFF, 0xF5, 0xF5, 0xF5);
	const Color Color::Yellow(0xFF, 0xFF, 0xFF, 0x00);
	const Color Color::YellowGreen(0xFF, 0x9A, 0xCD, 0x32);
}