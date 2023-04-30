//
//  Stopwatch.cpp
//  File file is part of the "Time" project and released under the MIT License.
//
//  Created by Samuel Williams on 28/6/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#include "Stopwatch.hpp"

#include <stdexcept>

namespace Time
{
	void Stopwatch::reset() noexcept
	{
		_total = Duration();
		_running = false;
	}
	
	Duration Stopwatch::time() const noexcept
	{
		if (_running) {
			return _total + Timer::time();
		} else {
			return _total;
		}
	}

	void Stopwatch::start()
	{
		if (_running) {
			throw std::logic_error("Stopwatch already started.");
		} else {
			Timer::reset();
			_running = true;
		}
	}
	
	Duration Stopwatch::stop()
	{
		if (_running) {
			auto duration = Timer::time();
			
			_running = false;
			_total += duration;
			
			return duration;
		} else {
			throw std::logic_error("Stopwatch not started.");
		}
	}
}
