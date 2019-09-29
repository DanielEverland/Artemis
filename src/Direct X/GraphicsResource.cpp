#include "..\\Exceptions\NullReferenceException.h"

#include "GraphicsResource.h"

GraphicsResource::GraphicsResource(shared_ptr<GraphicsDevice> graphicsDevice)
{
	this->graphicsDevice = graphicsDevice;
}
shared_ptr<GraphicsDevice> GraphicsResource::GetGraphicsDevice()
{
	if (graphicsDevice.use_count() == 0)
		throw NullReferenceException("Failed creating GraphicsResource. GraphicsDevice has expired!");

	return shared_ptr<GraphicsDevice>(graphicsDevice);
}