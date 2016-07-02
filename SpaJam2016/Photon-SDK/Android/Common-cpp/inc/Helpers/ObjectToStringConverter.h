/* Exit Games Common - C++ Client Lib
 * Copyright (C) 2004-2016 by Exit Games GmbH. All rights reserved.
 * http://www.photonengine.com
 * mailto:developer@photonengine.com
 */

#pragma once

#include "Common-cpp/inc/JString.h"
namespace ExitGames
{
	namespace Common
	{
		namespace Helpers
		{
			template<typename Etype>
			class ObjectToStringConverter
			{
			public:
				static JString toString(Etype* data, unsigned int size, bool withTypes=false);
			};

			template<typename Etype>
			class ObjectToStringConverter<Etype*>
			{
			public:
				static JString toString(Etype** data, unsigned int size, bool withTypes=false);
			};



			template<typename Etype>
			JString ObjectToStringConverter<Etype>::toString(Etype* data, unsigned int size, bool withTypes)
			{
				JString retStr = L"[";
				for(unsigned int i=0; i<size; ++i)
				{
					retStr += data[i].toString(withTypes);
					if(i < size-1)
						retStr += L", ";
				}
				retStr += L"]";
				return retStr;
			}

			template<typename Etype>
			JString ObjectToStringConverter<Etype*>::toString(Etype** data, unsigned int size, bool withTypes)
			{
				JString retStr = L"[";
				for(unsigned int i=0; i<size; ++i)
				{
					retStr += data[i]->toString(withTypes);
					if(i < size-1)
						retStr += L", ";
				}
				retStr += L"]";
				return retStr;
			}
		}
	}
}