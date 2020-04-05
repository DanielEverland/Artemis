#include "RenderStateGroups.h"

#include "RasterizerState.h"

RasterizerState RenderStateGroups::solidState = RasterizerState();

RasterizerState* RenderStateGroups::GetSolidState()
{
	return &solidState;
}

void RenderStateGroups::CreateStateGroups(const class GraphicsDevice* device)
{
	solidState = RasterizerState(device);
}
