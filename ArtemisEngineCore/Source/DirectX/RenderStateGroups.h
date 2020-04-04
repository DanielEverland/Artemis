#pragma once

#include "RasterizerState.h"

class RenderStateGroups
{
	friend class Renderer;

public:
	static RasterizerState* GetSolidState();

private:
	static RasterizerState solidState;

	static void CreateStateGroups(const class GraphicsDevice* device);
};