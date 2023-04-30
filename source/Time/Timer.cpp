//
//  Timer.cpp
//  File file is part of the "Time" project and released under the MIT License.
//
//  Created by Samuel Williams on 28/6/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#include "Timer.hpp"

#include <iomanip>

namespace Time
{
	Timer::Timer(const Clock & clock) noexcept : _clock(clock)
	{
		reset();
	}
	
	void Timer::reset() noexcept {
		_last = Timestamp(_clock);
	}

	Duration Timer::time() const noexcept {
		return Duration(_last);
	}
}
