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

		inline bool GetUseWARPAdapter() const { return useWARPAdapter; }
		inline void SetUseWARPAdapter(bool value) { useWARPAdapter = value; }

	private:
		static const uint8_t swapChainBufferSize = 3;

		static const D3D12_MESSAGE_SEVERITY BreakOnSeverity[];
		static D3D12_MESSAGE_SEVERITY IgnoreSeverity[];
		static D3D12_MESSAGE_ID IgnoreMessages[];
		static D3D12_MESSAGE_CATEGORY IgnoreCategories[];

		bool useWARPAdapter = false;

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
		virtual void CreateWindowClass() const;
		virtual HWND CreateWindowHandle();

		void EnableDebugLayer() const;
		ComPtr<IDXGIAdapter4> GetAdapter();
		bool IsAdapterDirectX12Compatible(const ComPtr<IDXGIAdapter1> adapter) const;
		bool IsWARPAdapater(const DXGI_ADAPTER_DESC1& adapter) const;
		void GetBestGraphicsAdapater(const ComPtr<IDXGIFactory4> dxgiFactory, ComPtr<IDXGIAdapter1> dxgiAdapter1, ComPtr<IDXGIAdapter4> dxgiAdapter4) const;
		ComPtr<ID3D12Device2> CreateDevice(ComPtr<IDXGIAdapter4> adapter) const;
		void EnableDebugMessages() const;
		ComPtr<ID3D12CommandQueue> CreateCommandQueue(ComPtr<ID3D12Device2> device, D3D12_COMMAND_LIST_TYPE type) const;
		bool CheckTearingSupport() const;
	};
}