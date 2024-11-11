#pragma once

#include "build.h"

#define GENERATION_LENGTH 256

//each Generation consists of 256 builds, where [0,1] are the best of last Generation aka new parents
struct Generation{
	struct Build builds[GENERATION_LENGTH];
};
