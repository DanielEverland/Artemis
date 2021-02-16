#pragma once

#pragma warning(push, 0)
#include <Windows.h>
#include <DbgHelp.h>
#include <stdexcept>
#pragma warning(pop)

using std::string;

class Exception : public std::runtime_error
{
public:
	explicit Exception(const std::exception& e) : runtime_error(e.what()) { CreateStacktrace(); }
	explicit Exception(const string& message) : runtime_error(message.c_str()) { CreateStacktrace(); }
	explicit Exception(const char* const message) : runtime_error(message) { CreateStacktrace(); }

	static bool InitializeSymbols();

	string GetStackTrace() const { return stackTrace; }
	string GetMessage() const { return what(); }
	string GetTypeName() const;
	string ToString() const;

	operator string() const;
	bool operator==(const Exception& other) const;

private:
	static const unsigned long FramesToSkip;
	static const unsigned long FramesToCapture;
	static const unsigned long MaximumNameLength;
	static const unsigned long long SymbolBufferSize;

	static HANDLE processHandle;
	static string CallstackLineIdentifier;

	string stackTrace;

	void CreateStacktrace();
	string GetPrettyFileName(const char* fileName) const;
	SYMBOL_INFO* CreateInfoPointer(ULONG64* buffer) const;
	IMAGEHLP_LINE CreateFileLineStruct() const;
	bool TryGetSymbolInfo(const void* const address, DWORD64* displacement, SYMBOL_INFO* info) const;
	bool TryGetFileInfo(const void* const address, const DWORD64* const displacement, IMAGEHLP_LINE* const linePointer) const;
	void AppendFrame(const SYMBOL_INFO* const info);
	void AppendFrameWithFileData(const SYMBOL_INFO* const info, const IMAGEHLP_LINE* const line);
};