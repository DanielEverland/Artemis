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

#include "StringUtility.h"
#include "Color.h"

// IO
using std::cout;
using std::cin;

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