#pragma once

#include "../../Core/Debugging/Verbosity.h"
#include "../../Core/Debugging/Logger.h"

#define TRY_START try{
#define TRY_END(Category, Verbosity) TRY_END_CUSTOM(Category, Verbosity, "")

#define TRY_END_CUSTOM(Category, Verbosity, CustomMessage) }catch (const Exception& e) \
{ Logger::Log(Category, Verbosity, "\nUncaught exception: " + std::string(CustomMessage) + "\n" + e.ToString()); } \
catch (const std::exception& e) \
{ Logger::Log(Category, Verbosity, "\nUncaught std exception: " + std::string(CustomMessage) + "\n" + std::string(e.what())); }