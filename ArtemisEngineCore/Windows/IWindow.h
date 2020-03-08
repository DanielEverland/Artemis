#pragma once

#include <windows.h>

namespace ArtemisWindow
{
	class IWindow
	{
	public:
		virtual bool IsFullscreen() const = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual void SetWidth(unsigned int newWidth) = 0;

		virtual unsigned int GetHeight() const = 0;
		virtual void SetHeight(unsigned int newHeight) = 0;

		virtual void Resize(unsigned int width, unsigned int height) = 0;

		virtual HWND GetHandle() const = 0;

		inline bool IsWindowed() const { return !IsFullscreen(); }
	};
}