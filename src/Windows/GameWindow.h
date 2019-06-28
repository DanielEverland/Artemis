#include "Window.h"

namespace ArtemisWindow
{
	class GameWindow : public Window
	{
	public:
		explicit GameWindow(HINSTANCE handleInstance, const LPCWSTR className, int windowState);

	private:
		virtual void RunMessageLoop() final;
	};
}