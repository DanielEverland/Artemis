#pragma once

class Application
{
public:
	static void SetVSync(bool enabled);
	static bool GetVSync();

private:
	bool static useVSync;
};