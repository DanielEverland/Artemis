#include "Exception.h"

using namespace ArtemisEngine;

Exception::Exception(const std::exception& e) : runtime_error(e.what())
{
}

Exception::Exception(const string& message) : runtime_error(message.c_str())
{
}

Exception::Exception(const char* const message) : runtime_error(message)
{
}
