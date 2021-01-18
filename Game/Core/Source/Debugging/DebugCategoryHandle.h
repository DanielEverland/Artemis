#pragma once

#include <functional>
//
//using std::less;

struct DebugCategoryHandle
{
public:
	DebugCategoryHandle();
	DebugCategoryHandle(const DebugCategoryHandle& other);
	DebugCategoryHandle(DebugCategoryHandle&& other) noexcept;

	static int GetCurrentHandleID();
	
	int GetHandleID() const;

	DebugCategoryHandle& operator=(const DebugCategoryHandle& other);
	DebugCategoryHandle& operator=(DebugCategoryHandle&& other) noexcept;

	operator int() { return GetHandleID(); }
	operator int() const { return GetHandleID(); }
	
private:
	static int HandleCount;

	int HandleID;

	static int GetNextHandleID();
};

//template<> struct less<DebugCategoryHandle>
//{
//	bool operator() (const DebugCategoryHandle& lhs, const DebugCategoryHandle& rhs) const
//	{
//		return lhs.GetHandleID() < rhs.GetHandleID();
//	}
//};