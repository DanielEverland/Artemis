#include "SDLException.h"

SDLException::SDLException(const std::string& Message) : Exception(Message)
{
}

SDLException::SDLException(const char* Message) : Exception(Message)
{
}
