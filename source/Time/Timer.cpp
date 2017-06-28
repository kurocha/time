//
//  Timer.cpp
//  File file is part of the "Time" project and released under the MIT License.
//
//  Created by Samuel Williams on 28/6/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#include "Timer.hpp"

namespace Time
{
	Timer::Timer(const Clock & clock) noexcept : _clock(clock)
	{
		reset();
	}
	
	void Timer::reset() noexcept {
		_last = Interval(_clock);
	}

	Interval Timer::time() const noexcept {
		auto current = Interval(_clock);
		return current - _last;
	}
}
