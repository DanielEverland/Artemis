#include <memory>

#include "GraphicsDevice.h"

using std::shared_ptr;
using std::weak_ptr;

class GraphicsResource
{
protected:
	GraphicsResource(shared_ptr<GraphicsDevice> graphicsDevice);

	shared_ptr<GraphicsDevice> GetGraphicsDevice() const;

private:

	weak_ptr<GraphicsDevice> graphicsDevice;
};