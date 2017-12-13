#ifndef SHARED_HEADER_H
#define SHARED_HEADER_H

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <cmath>

#ifdef linux
#include <pthread.h>
#include <zconf.h>
#include <time.h>
#endif

#define GRID_SIZE_X 256
#define GRID_SIZE_Y 64

#endif