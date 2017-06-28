//
//  Timer.hpp
//  File file is part of the "Time" project and released under the MIT License.
//
//  Created by Samuel Williams on 28/6/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#pragma once

#include "Interval.hpp"

namespace Time
{
	class Timer {
	protected:
		const Clock _clock;
		Interval _last;
		
	public:
		/// Resets the timer using the given clock.
		Timer(const Clock & clock = Clock::MONOTONIC) noexcept;
		
		/// Reset the timer back to 0.
		void reset() noexcept;
		
		/// The amount of time since the last call to reset.
		Interval time() const noexcept;
	};
}
