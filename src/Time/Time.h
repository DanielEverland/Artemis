#pragma once

#include "..\Windows\Window.h"

namespace ArtemisWindow
{
	class GameWindow;
}

class Time
{
public:
	static inline unsigned int GetFrameCount() { return frameCount; }
	
private:
	static unsigned int frameCount;
		
	friend class ArtemisWindow::GameWindow;
};