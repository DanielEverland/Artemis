#pragma once

class IDeallocator
{
public:
	virtual ~IDeallocator() = default;
	
	virtual void Deallocate(const void* const block) = 0;
};
