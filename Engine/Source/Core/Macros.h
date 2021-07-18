#pragma once

#define NO_WARNING_BEGIN __pragma(warning(push, 0))
#define NO_WARNING_END __pragma(warning(pop))

#define NO_WARNING(expression) \
NO_WARNING_BEGIN \
expression \
NO_WARNING_END

#define ENABLE_ASSERT _DEBUG

#ifdef ENABLE_ASSERT
#define Assert(expression, exception) if (!(expression)) { throw (exception); }
#else
#define Assert(expression, exception)
#endif