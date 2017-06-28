//
//  Timeout.hpp
//  File file is part of the "Time" project and released under the MIT License.
//
//  Created by Samuel Williams on 28/6/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#pragma once

#include "Stopwatch.hpp"

namespace Time
{
	class Timeout : public Stopwatch
	{
	protected:
		Interval _duration;
		
	public:
		Timeout(const Interval & duration, const Clock & clock = Clock::MONOTONIC) noexcept : Stopwatch(clock), _duration(duration) {}
		
		const Interval & duration() const noexcept {return _duration;}
		
		/// Returns whether the duration has passed.
		bool expired() const noexcept;

		/// This function returns the time remaining, which may be negative if the Stopwatch has gone past the timeout.
		Interval remaining() const noexcept;
	};
}
