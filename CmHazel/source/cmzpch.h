#pragma once

#include "CmHazel/Core/PlatformDetection.h"

#ifdef CM_PLATFORM_WINDOWS
	#ifndef NOMINMAX
		// See github.com/skypjack/entt/wiki/Frequently-Asked-Questions#warning-c4003-the-min-the-max-and-the-macro
		#define NOMINMAX
	#endif // !NOMINMAX
#endif // CM_PLATFORM_WINDOWS


#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <string>
#include <sstream>
#include <array>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "CmHazel/Core/Base.h"

#include "CmHazel/Core/Log.h"

#include "CmHazel/Debug/Instrumentor.h"

#ifdef CM_PLATFORM_WINDOWS
	#include <Windows.h>
#endif // CM_PLATFORM_WINDOWS
