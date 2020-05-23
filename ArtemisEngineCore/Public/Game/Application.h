#pragma once

namespace ArtemisEngine
{
	class Application
	{
	public:
		static void SetVSync(bool enabled);
		static bool GetVSync();

	private:
		bool static useVSync;
	};
}