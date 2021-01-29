#include "GlobalState.h"

GlobalState::GlobalState()
{
	State = std::make_unique<LuaState>(LuaState());
}

GlobalState::operator LuaState*() const
{
	return State.get();
}
