#pragma once

class IDeallocator
{
public:
	virtual ~IDeallocator() = default;
	
	virtual void Deallocate(void* block) = 0;
};
