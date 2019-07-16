#pragma once

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

// The min/max macros conflict with like-named member functions.
// Only use std::min and std::max defined in <algorithm>.
#if defined(min)
#undef min
#endif

#if defined(max)
#undef max
#endif

using namespace Microsoft::WRL;

using std::chrono::milliseconds;

namespace ArtemisWindow
{
	class GameWindow : public Window
	{
	public:
		explicit GameWindow(HINSTANCE handleInstance, const LPCWSTR className, int windowState);

		inline bool GetUseWARPAdapter() const { return useWARPAdapter; }
		inline void SetUseWARPAdapter(bool value) { useWARPAdapter = value; }

		virtual void Show();

	private:
		static const bool AllowAltEnterFullscreen = false;
		static const uint8_t swapChainBufferSize = 3;

		static const D3D12_MESSAGE_SEVERITY BreakOnSeverity[];
		static D3D12_MESSAGE_SEVERITY IgnoreSeverity[];
		static D3D12_MESSAGE_ID IgnoreMessages[];
		static D3D12_MESSAGE_CATEGORY IgnoreCategories[];

		static Color BackbufferColor;

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
		virtual DXGI_SWAP_CHAIN_DESC1 GetSwapChainDescription(uint32_t width, uint32_t height, uint32_t bufferCount) const;

		void Update();
		void Render();
		void Resize(uint32_t width, uint32_t height);
		void SetFullscreen(bool fullscreen);

		// Messages
		virtual LONG_PTR HandleMessage(UINT messageCode, UINT_PTR wParam, LONG_PTR lParam);
		virtual void OnPaint();
		virtual void OnSystemKeyDown(UINT_PTR wParam);
		virtual void OnSystemKeyUp(UINT_PTR wParam);
		virtual void OnKeyDown(UINT_PTR wParam);
		virtual void OnKeyUp(UINT_PTR wParam);
		virtual void OnResize();
		virtual void OnClose();

		void HandleKeyDown(UINT_PTR wParam);

		void InitializeDirectX();
		void EnableDebugLayer() const;
		ComPtr<IDXGIAdapter4> GetAdapter();
		bool IsAdapterDirectX12Compatible(const ComPtr<IDXGIAdapter1> adapter) const;
		bool IsWARPAdapater(const DXGI_ADAPTER_DESC1& adapter) const;
		void GetBestGraphicsAdapater(const ComPtr<IDXGIFactory4> dxgiFactory, ComPtr<IDXGIAdapter1> dxgiAdapter1, ComPtr<IDXGIAdapter4> dxgiAdapter4) const;
		ComPtr<ID3D12Device2> CreateDevice(ComPtr<IDXGIAdapter4> adapter) const;
		void EnableDebugMessages(ComPtr<ID3D12Device2> device) const;
		ComPtr<ID3D12CommandQueue> CreateCommandQueue(ComPtr<ID3D12Device2> device, D3D12_COMMAND_LIST_TYPE type) const;
		bool CheckTearingSupport() const;
		ComPtr<IDXGISwapChain4> CreateSwapChain(HWND handle, ComPtr<ID3D12CommandQueue> commandQueue, uint32_t width, uint32_t height, uint32_t bufferCount) const;
		ComPtr<ID3D12DescriptorHeap> CreateDescriptorHeap(ComPtr<ID3D12Device2> device, D3D12_DESCRIPTOR_HEAP_TYPE type, uint32_t numDescriptors) const;
		void UpdateRenderTargetViews(ComPtr<ID3D12Device2> device, ComPtr<IDXGISwapChain4> swapChain, ComPtr<ID3D12DescriptorHeap> descriptorHeap);
		ComPtr<ID3D12CommandAllocator> CreateCommandAllocator(ComPtr<ID3D12Device2> device, D3D12_COMMAND_LIST_TYPE type) const;
		ComPtr<ID3D12GraphicsCommandList> CreateCommandList(ComPtr<ID3D12Device2> device, ComPtr<ID3D12CommandAllocator> commandAllocator, D3D12_COMMAND_LIST_TYPE type) const;
		ComPtr<ID3D12Fence> CreateFence(ComPtr<ID3D12Device2> device) const;
		HANDLE CreateEventHandle() const;
		uint64_t Signal(ComPtr<ID3D12CommandQueue> commandQueue, ComPtr<ID3D12Fence> fence, uint64_t& fenceValue) const;
		void Flush(ComPtr<ID3D12CommandQueue> commandQueue, ComPtr<ID3D12Fence> fence, uint64_t& fenceValue, HANDLE fenceEvent) const;
		void WaitForFenceValue(ComPtr<ID3D12Fence> fence, uint64_t fenceValue, HANDLE fenceEvent, milliseconds duration = milliseconds::max()) const;
	};
}