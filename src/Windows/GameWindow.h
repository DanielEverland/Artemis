#define WIN32_LEAN_AND_MEAN
#include <windows.h>

// Windows Runtime Library. Needed for Microsoft::WRL::ComPtr<> template class.
#include <wrl.h>

// DirectX 12 specific headers.
#include <d3d12.h>
#include <dxgi1_6.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

// D3D12 extension library.
#include "..\Direct X\d3dx12.h"

// STL Headers
#include <algorithm>
#include <cassert>
#include <chrono>

#include "Window.h"

using namespace Microsoft::WRL;

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