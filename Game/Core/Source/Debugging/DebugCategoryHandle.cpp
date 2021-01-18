// Invisible Walls is the sole owner of all rights of, and to the video game First Class Trouble and affiliated projects and retains all rights to concepts and ideas from First Class Trouble, which are not transferred herein, and retains all common law copyrights and trademarks to the given title.
#include "DebugCategoryHandle.h"

int DebugCategoryHandle::HandleCount = 0;

DebugCategoryHandle::DebugCategoryHandle() : HandleID(GetNextHandleID())
{
}

DebugCategoryHandle::DebugCategoryHandle(const DebugCategoryHandle& other) : HandleID(other.HandleID)
{
}

DebugCategoryHandle::DebugCategoryHandle(DebugCategoryHandle&& other) noexcept : HandleID(other.HandleID)
{
}

int DebugCategoryHandle::GetCurrentHandleID()
{
	return HandleCount;
}

int DebugCategoryHandle::GetHandleID() const
{
	return HandleID;
}

DebugCategoryHandle& DebugCategoryHandle::operator=(const DebugCategoryHandle& other)
{
	if (this == &other)
		return *this;
	HandleID = other.HandleID;
	return *this;
}

DebugCategoryHandle& DebugCategoryHandle::operator=(DebugCategoryHandle&& other) noexcept
{
	if (this == &other)
		return *this;
	HandleID = other.HandleID;
	return *this;
}

int DebugCategoryHandle::GetNextHandleID()
{
	return ++HandleCount;
}
