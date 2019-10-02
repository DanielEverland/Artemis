#include "..\\Exceptions\NullReferenceException.h"

#include "GraphicsResource.h"

GraphicsResource::GraphicsResource(const shared_ptr<const GraphicsDevice> graphicsDevice)
{
	this->graphicsDevice = graphicsDevice;
}
const shared_ptr<const GraphicsDevice> GraphicsResource::GetGraphicsDevice() const
{
	if (graphicsDevice.use_count() == 0)
		throw NullReferenceException("GraphicsDevice has expired!");

	return shared_ptr<const GraphicsDevice>(graphicsDevice);
}