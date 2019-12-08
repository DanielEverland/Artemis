#include "Input.h"

#include "Time/Time.h"
#include "Exceptions/InvalidArgumentException.h"
#include "Debugging/Output.h"

const float Input::ClickInterval = 0.2f;
const int Input::KeyboardStateCurrentFlag = 0x8000;

map Input::keyBuffer = { };
set Input::clickedKeys = { };

bool Input::IsDown(const Key key)
{
	return CompareKeyState(key, KeyState::Down);
}

bool Input::IsUp(const Key key)
{
	return CompareKeyState(key, KeyState::Up);
}

bool Input::IsStay(const Key key)
{
	return CompareKeyState(key, KeyState::Stay);
}

bool Input::IsClicked(const Key key)
{
	return clickedKeys.find(key) != clickedKeys.end();
}

bool Input::IsAny(const Key key)
{
	return keyBuffer.find(key) != keyBuffer.end() || IsClicked(key);
}

void Input::OnKeyDown(const Key key)
{
	auto iterator = keyBuffer.find(key);
	if (iterator == keyBuffer.end())
	{
		KeyInfo info(KeyState::Down, Time::GetTimeSinceStart());
		keyBuffer.insert(pair(key, info));
	}
}

void Input::OnKeyUp(const Key key)
{
	auto iterator = keyBuffer.find(key);
	if (iterator != keyBuffer.end())
	{
		float currentTime = Time::GetTimeSinceStart();

		if (IsValidClickEvent(iterator->second.downTime, currentTime))
			clickedKeys.insert(key);

		iterator->second.State = KeyState::Up;
	}
}

bool Input::IsValidClickEvent(float downTime, float upTime)
{
	return upTime - downTime < ClickInterval;
}

void Input::ClearClicks()
{
	clickedKeys.clear();
}

void Input::ClearDowns()
{
	for (auto i = keyBuffer.begin(); i != keyBuffer.end(); i++)
	{
		KeyState currentState = i->second.State;

		if(currentState == KeyState::Down)
			i->second.State = KeyState::Stay;
	}
}

void Input::ClearUps()
{
	auto i = keyBuffer.begin();
	while (i != keyBuffer.end())
	{
		if (i->second.State == KeyState::Up)
			keyBuffer.erase((i++)->first);
		else
			i++;
	}
}

void Input::EndOfFrame()
{
	ClearClicks();
	ClearUps();
	ClearDowns();
}

bool Input::CompareKeyState(Key key, KeyState state)
{
	auto iter = keyBuffer.find(key);
	if (iter != keyBuffer.end())
		return iter->second.State == state;

	return false;
}

Key Input::UpWParamToKey(UINT_PTR wParam)
{
	switch (wParam)
	{
	case VK_SHIFT:
		return GetUpShiftKey();
	case VK_CONTROL:
		return GetUpControlKey();
	case VK_MENU:
		return GetUpAltKey();
	default:
		return Key(wParam);
	}
}

Key Input::DownWParamToKey(UINT_PTR wParam)
{
	switch (wParam)
	{
	case VK_SHIFT:
		return GetDownShiftKey();
	case VK_CONTROL:
		return GetDownControlKey();
	case VK_MENU:
		return GetDownAltKey();
	default:
		return Key(wParam);
	}	
}

bool Input::IsKeyPressed(UINT_PTR virtualKey)
{
	return GetKeyState(int(virtualKey)) & KeyboardStateCurrentFlag;
}

bool Input::IsKeyInBuffer(Key key)
{
	return keyBuffer.find(key) != keyBuffer.end();
}

void Input::SanitizeDownKeys()
{
	for (auto i = keyBuffer.begin(); i != keyBuffer.end(); i++)
	{
		if (i->second.State != KeyState::Up)
		{
			if (!IsKeyPressed(UINT_PTR(i->first)))
			{
				OnKeyUp(i->first);
			}
		}
	}
}

Key Input::GetUpShiftKey()
{
	if (!IsKeyPressed(VK_LSHIFT) && IsKeyInBuffer(Key::LeftShift))
		return Key::LeftShift;
	else if (!IsKeyPressed(VK_RSHIFT) && IsKeyInBuffer(Key::RightShift))
		return Key::RightShift;
	else
		throw InvalidArgumentException("No shift key pressed");
}

Key Input::GetUpControlKey()
{
	if (!IsKeyPressed(VK_LCONTROL) && IsKeyInBuffer(Key::LeftControl))
		return Key::LeftControl;
	else if (!IsKeyPressed(VK_RCONTROL) && IsKeyInBuffer(Key::RightControl))
		return Key::RightControl;
	else
		throw InvalidArgumentException("No control key pressed");
}

Key Input::GetUpAltKey()
{
	if (!IsKeyPressed(VK_LMENU) && IsKeyInBuffer(Key::LeftAlt))
		return Key::LeftAlt;
	else if (!IsKeyPressed(VK_RMENU) && IsKeyInBuffer(Key::RightAlt))
		return Key::RightAlt;
	else
		throw InvalidArgumentException("No alt key pressed");
}

Key Input::GetDownShiftKey()
{
	if (IsKeyPressed(VK_LSHIFT))
		return Key::LeftShift;
	else if (IsKeyPressed(VK_RSHIFT))
		return Key::RightShift;
	else
		throw InvalidArgumentException("No shift key pressed");
}

Key Input::GetDownControlKey()
{
	if (IsKeyPressed(VK_LCONTROL))
		return Key::LeftControl;
	else if (IsKeyPressed(VK_RCONTROL))
		return Key::RightControl;
	else
		throw InvalidArgumentException("No control key pressed");
}

Key Input::GetDownAltKey()
{
	if (IsKeyPressed(VK_LMENU))
		return Key::LeftAlt;
	else if (IsKeyPressed(VK_RMENU))
		return Key::RightAlt;
	else
		throw InvalidArgumentException("No alt key pressed");
}