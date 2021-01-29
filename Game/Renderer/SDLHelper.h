﻿#pragma once

#include<iostream>
#include<SDL.h>
#include"SDLException.h"

#define THROW_IF_FAILED(result) if((result) < 0) { throw SDLException("SDL exception: " + std::string(SDL_GetError())); } 