#include "Window.h"

namespace ArtemisWindow
{
	class GameWindow : public Window
	{
	public:
		explicit GameWindow(HandleInstance handleInstance, const UnicodeChar* className, int windowState);

	private:
		virtual void RunMessageLoop() final;
	};
}