#pragma once

#include <d3d12.h>
#include <wrl.h>

#include <cstdint>
#include <queue>

using namespace Microsoft::WRL;

using std::queue;

class CommandQueue
{
public:
	explicit CommandQueue(ComPtr<ID3D12Device2> device, D3D12_COMMAND_LIST_TYPE type);
	virtual ~CommandQueue();

	ComPtr<ID3D12GraphicsCommandList2> GetCommandList();
	
	uint64_t ExecuteCommandList(ComPtr<ID3D12GraphicsCommandList2> commandList);

	uint64_t Signal();
	bool IsFenceComplete(uint64_t fenceValue);
	void WaitForFenceValue(uint64_t fenceValue);
	void Flush();

	ComPtr<ID3D12CommandQueue> GetD3D12CommandQueue() const;

protected:
	ComPtr<ID3D12CommandAllocator> CreateCommandAllocator();
	ComPtr<ID3D12GraphicsCommandList2> CreateCommandList(ComPtr<ID3D12CommandAllocator> allocator);

private:
	
	struct CommandAllocatorEntry
	{
		uint64_t fenceValue;
		ComPtr<ID3D12CommandAllocator> commandAllocator;
	};

#pragma warning(disable : 26812)
	static const D3D12_COMMAND_QUEUE_PRIORITY DefaultCommandQueuePriority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
	static const D3D12_COMMAND_QUEUE_FLAGS DefaultCommandQueueFlags = D3D12_COMMAND_QUEUE_FLAG_NONE;
#pragma warning(default : 26812)

	D3D12_COMMAND_LIST_TYPE	commandListType;
	ComPtr<ID3D12Device2> device;
	ComPtr<ID3D12CommandQueue> commandQueue;

	ComPtr<ID3D12Fence>	fence;
	HANDLE fenceEvent;
	uint64_t fenceValue;

	queue<CommandAllocatorEntry> commandAllocatorQueue;
	queue<ComPtr<ID3D12GraphicsCommandList2>> commandListQueue;
};