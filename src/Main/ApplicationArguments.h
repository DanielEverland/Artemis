#pragma once

#include <memory>

using std::shared_ptr;

class ApplicationArguments
{
public:
	static void Initialize();

	inline static bool HasWidth() { return width != nullptr; }
	inline static long GetWidth() { return *width; }

	inline static bool HasHeight() { return height != nullptr; }
	inline static long GetHeight() { return *height; }

	inline static bool HasUseWARP() { return useWARPDefined; }

private:
	static shared_ptr<long> width;
	static shared_ptr<long> height;
	static bool useWARPDefined;
};