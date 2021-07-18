#pragma once

#include <d3d11.h>
#include <wrl.h>
#include <format>

#include "Exception/DirectXException.h"

using namespace Microsoft::WRL;

constexpr void CheckResult(HRESULT result, const string& message)
{
	if (result != S_OK)
		throw ArtemisEngine::DirectXException(std::format("{}. ErrorCode: {}", message, std::to_string(result)));
}