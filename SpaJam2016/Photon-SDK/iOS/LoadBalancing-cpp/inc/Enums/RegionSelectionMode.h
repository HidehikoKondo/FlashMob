/* Exit Games Photon LoadBalancing - C++ Client Lib
 * Copyright (C) 2004-2016 by Exit Games GmbH. All rights reserved.
 * http://www.photonengine.com
 * mailto:developer@photonengine.com
 */

#pragma once

#include "Common-cpp/inc/Common.h"

namespace ExitGames
{
	namespace LoadBalancing
	{
		namespace RegionSelectionMode
		{
			static const nByte DEFAULT   = 0;
			static const nByte SELECT    = 1;
#ifdef EG_PLATFORM_SUPPORTS_CPP11
			static const nByte BEST      = 2;
#endif
		}
		/** @file */
	}
}