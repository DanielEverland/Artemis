#pragma once

#include <map>
#include <set>

#include "..\\Input\Key.h"

namespace ArtemisWindow
{
	class GameWindow;
}

enum class KeyState
{
	Down,
	Stay,
	Up,
};

struct KeyInfo
{
public:
	KeyInfo(KeyState state, float time)
	{
		State = state;
		downTime = time;
	}

	KeyState State;
	float downTime;
};

using set = std::set<Key>;
using map = std::map<Key, KeyInfo>;
using pair = std::pair<Key, KeyInfo>;

class Input
{
	friend class ArtemisWindow::GameWindow;

public:
	static bool IsDown(const Key key);
	static bool IsUp(const Key key);
	static bool IsStay(const Key key);
	static bool IsClicked(const Key key);
	static bool IsAny(const Key key);

private:
	static const float ClickInterval;
	static const int KeyboardStateCurrentFlag;

	static map keyBuffer;
	static set clickedKeys;
	
	static void OnKeyDown(const Key key);
	static void OnKeyUp(const Key key);
	static bool IsValidClickEvent(float downTime, float upTime);
	static void ClearClicks();
	static void ClearDowns();
	static void ClearUps();
	static void EndOfFrame();
	static void SanitizeDownKeys();

	static bool CompareKeyState(Key key, KeyState state);

	static Key DownWParamToKey(UINT_PTR wParam);
	static Key UpWParamToKey(UINT_PTR wParam);

	static bool IsKeyPressed(UINT_PTR virtualKey);
	static bool IsKeyInBuffer(Key key);

	static Key GetDownShiftKey();
	static Key GetDownControlKey();
	static Key GetDownAltKey();

	static Key GetUpShiftKey();
	static Key GetUpControlKey();
	static Key GetUpAltKey();
};