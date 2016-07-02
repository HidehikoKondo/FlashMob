/* Exit Games Photon Chat - C++ Client Lib
 * Copyright (C) 2004-2016 by Exit Games GmbH. All rights reserved.
 * http://www.photonengine.com
 * mailto:developer@photonengine.com
 */

#include "Chat-cpp/inc/AuthenticationValues.h"
#include "Chat-cpp/inc/Internal/AuthenticationValuesSecretSetter.h"

namespace ExitGames
{
	namespace Chat
	{
		namespace Internal
		{
			void AuthenticationValuesSecretSetter::setSecret(AuthenticationValues& authenticationValues, const Common::JString& secret)
			{
				authenticationValues.setSecret(secret);
			}
		}
	}
}