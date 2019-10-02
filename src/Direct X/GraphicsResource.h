#include <memory>

#include "GraphicsDevice.h"

using std::shared_ptr;
using std::weak_ptr;

class GraphicsResource
{
protected:
	explicit GraphicsResource(const shared_ptr<const GraphicsDevice> graphicsDevice);

	const shared_ptr<const GraphicsDevice> GetGraphicsDevice() const;

private:
	weak_ptr<const GraphicsDevice> graphicsDevice;
};