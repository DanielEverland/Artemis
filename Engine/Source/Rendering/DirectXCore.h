#pragma once

#include <d3d11.h>
#include <DirectXMath.h>
#include <d3dcompiler.h>

#include <wrl.h>
#include <format>

#include "Exception/DirectXException.h"

using namespace Microsoft::WRL;
using namespace DirectX;

constexpr void CheckResult(HRESULT result, const string& message)
{
	if (result != S_OK)
		throw ArtemisEngine::DirectXException(std::format("{}. ErrorCode: {}", message, std::to_string(result)));
}