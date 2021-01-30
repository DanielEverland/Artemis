#pragma once

#include <Game.h>

class SDLException : public Exception
{
public:
	explicit SDLException(const std::string& Message);
	explicit SDLException(const char* Message);
};
