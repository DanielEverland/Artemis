#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <DbgHelp.h>
#include <stdexcept>
#include <string>


using std::string;

class Exception : private std::runtime_error
{
public:
	explicit Exception(const std::exception& e) : runtime_error(e.what()) { CreateStacktrace(); }
	explicit Exception(const string& message) : runtime_error(message.c_str()) { CreateStacktrace(); }
	explicit Exception(const char* const message) : runtime_error(message) { CreateStacktrace(); }

	static bool InitializeSymbols();

	inline const string GetStackTrace() const { return stackTrace; }
	inline const string GetMessage() const { return what(); }
	const string GetTypeName() const;

	bool operator==(const Exception& other) const;
	
private:
	static const unsigned long FramesToSkip;
	static const unsigned long FramesToCapture;
	static const unsigned long MaximumNameLength;
	static const unsigned long long SymbolBufferSize;

	static HANDLE processHandle;

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

class InvalidArgumentException : public Exception
{
public:
	explicit InvalidArgumentException(const std::exception& e) : Exception(e) { }
	explicit InvalidArgumentException(const string& message) : Exception(message) { }
	explicit InvalidArgumentException(const char* const message) : Exception(message) { }
};

class DirectXException : public Exception
{
public:
	explicit DirectXException(const std::exception& e) : Exception(e) { }
	explicit DirectXException(const string& message) : Exception(message) { }
	explicit DirectXException(const char* const message) : Exception(message) { }
};