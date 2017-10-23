#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <cmath>

#ifdef _WIN32
#include <Windows.h>
#include "getopt.h"
#endif

#ifdef linux
#include <pthread.h>
#include <zconf.h>
#endif

#define GRID_SIZE_X 512
#define GRID_SIZE_Y 128