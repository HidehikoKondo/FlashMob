/* Exit Games Common - C++ Client Lib
 * Copyright (C) 2004-2016 by Exit Games GmbH. All rights reserved.
 * http://www.photonengine.com
 * mailto:developer@photonengine.com
 */

#pragma once

#include "Common-cpp/inc/defines.h"
#ifdef EG_PLATFORM_SUPPORTS_CPP11
#include <atomic>
#endif

namespace ExitGames
{
	namespace Common
	{
		namespace Helpers
		{
			class Spinlock
			{
			public:
				Spinlock(void);
				void lock(void);
				void unlock(void);
#ifdef EG_PLATFORM_SUPPORTS_CPP11
			private:
				std::atomic<bool> mLocked;
#endif
			};
		}
	}
}