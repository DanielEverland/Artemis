﻿#pragma once

#include "Include/Game/Matrix.h"

namespace ArtemisEngine::Rendering
{
	struct PerObjectConstantBuffer
	{
	public:
		XMFLOAT4X4 WorldViewProjMatrix;
	};
}
