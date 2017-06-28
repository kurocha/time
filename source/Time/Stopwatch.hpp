//
//  Stopwatch.hpp
//  File file is part of the "Time" project and released under the MIT License.
//
//  Created by Samuel Williams on 28/6/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#pragma once

#include "Timer.hpp"

namespace Time
{
	class Stopwatch : private Timer {
	protected:
		Interval _total = 0;
		bool _running = false;
		
	public:
		Stopwatch(const Clock & clock = Clock::MONOTONIC) noexcept : Timer(clock) {}
		
		/// Reset the stopwatch back to 0, it will be stopped.
		void reset() noexcept;
		
		/// The accumulated time since calling reset.
		Interval time() const noexcept;
		
		/// Start accumulating time.
		void start();
		
		/// Stop accumulating time. Returns the amount of time since calling `start()`.
		Interval stop();
		
		bool running() const noexcept
		{
			return _running;
		}
	};
}
