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

		inline uint32_t GetClientWidth() const { return clientWidth; }
		inline void SetClientWidth(uint32_t value) { clientWidth = value; }

		inline uint32_t GetClientHeight() const { return clientHeight; }
		inline void SetClientHeight(uint32_t value) { clientHeight = value; }

		inline bool GetUseWARPAdapter() const { return useWARPAdapter; }
		inline void SetUseWARPAdapter(bool value) { useWARPAdapter = value; }

	private:
		static const uint8_t swapChainBufferSize = 3;
		bool useWARPAdapter = false;

		uint32_t clientWidth = 1280;
		uint32_t clientHeight = 720;

		bool directXInitialized = false;

		RECT previousWindowRect;

		// DirectX 12 Objects
		ComPtr<ID3D12Device2> device;
		ComPtr<ID3D12CommandQueue> commandQueue;
		ComPtr<IDXGISwapChain4> swapChain;
		ComPtr<ID3D12Resource> backBuffers[swapChainBufferSize];
		ComPtr<ID3D12GraphicsCommandList> commandList;
		ComPtr<ID3D12CommandAllocator> commandAllocators[swapChainBufferSize];
		ComPtr<ID3D12DescriptorHeap> RTVDescriptorHeap;
		UINT RTVDescriptorSize;
		UINT currentBackBufferIndex;

		// Synchronization objects
		ComPtr<ID3D12Fence> fence;
		uint64_t fenceValue = 0;
		uint64_t frameFenceValues[swapChainBufferSize] = {};
		HANDLE fenceEvent;

		bool vSync = true;
		bool tearingSupported = false;
		bool fullscreen = false;

		virtual void RunMessageLoop() final;
	};
}