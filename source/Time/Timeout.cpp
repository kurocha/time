//
//  Timeout.cpp
//  File file is part of the "Time" project and released under the MIT License.
//
//  Created by Samuel Williams on 28/6/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#include "Timeout.hpp"

namespace Time
{
	bool Timeout::expired() const noexcept
	{
		return time() >= _duration;	
	}
	
	Duration Timeout::remaining() const noexcept
	{
		return _duration - time();
	}
}
