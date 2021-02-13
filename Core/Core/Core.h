#pragma once

#include <memory>
#include <string>
#include <iostream>

#include <map>
#include <vector>
#include <set>

#include "../IO/Path.h"
#include "../IO/Directory.h"
#include "../IO/JsonException.h"

#include "../Exceptions/IOException.h"
#include "../Exceptions/ArgumentException.h"
#include "../Exceptions/InvalidOperationException.h"

#include "../Debugging/Verbosity.h"
#include "../Debugging/Logger.h"

#include "../Config/GameConfiguration.h"

#include "StringUtility.h"
#include "Color.h"

#define TRY_START try{
#define TRY_END(Category, Verbosity) TRY_END_CUSTOM(Category, Verbosity, "")

#define TRY_END_CUSTOM(Category, Verbosity, CustomMessage) }catch (const Exception& e) \
{ Logger::Log(Category, Verbosity, "\nUncaught exception: " + std::string(CustomMessage) + "\n" + e.ToString()); } \
catch (const std::exception& e) \
{ Logger::Log(Category, Verbosity, "\nUncaught std exception: " + std::string(CustomMessage) + "\n" + std::string(e.what())); }

// IO
using std::cout;
using std::cin;
using std::endl;

// Memory
using std::unique_ptr;
using std::shared_ptr;
using std::weak_ptr;

// String
using std::string;

// Containers
using std::vector;
using std::map;
using std::set;