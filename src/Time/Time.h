#pragma once

#include "..\Windows\Window.h"

class Time
{
public:
	static inline unsigned int GetFrameCount() { return frameCount; }
	
private:
	static unsigned int frameCount;
	
	friend void TimeTick();
};