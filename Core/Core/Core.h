#pragma once

#include <memory>
#include <string>
#include <iostream>

#include <IO/Path.h>
#include <IO/Directory.h>

#include <INIReader/INIReader.h>

#include "StringUtility.h"
#include "GameConfiguration.h"

// IO
using std::cout;
using std::cin;

// Memory
using std::unique_ptr;
using std::shared_ptr;
using std::weak_ptr;

// String
using std::string;