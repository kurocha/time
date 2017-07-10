//
//  Interval.cpp
//  File file is part of the "Time" project and released under the MIT License.
//
//  Created by Samuel Williams on 28/6/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#include "Interval.hpp"

#include <iostream>
#include <iomanip>

namespace Time
{
	Interval::Interval(double seconds) noexcept
	{
		_value.tv_sec = seconds;
		_value.tv_nsec = (seconds - _value.tv_sec) * NS;
	}
	
	void Interval::sleep() noexcept
	{
		nanosleep(&_value, (struct timespec *)nullptr);
	}
	
	std::ostream & operator<<(std::ostream & out, const Interval & interval)
	{
		auto seconds = interval.seconds();
		auto nanoseconds = interval.nanoseconds();
		
		if (nanoseconds < 0) {
			seconds -= 1;
			nanoseconds += Interval::NS;
		} else if (nanoseconds >= Interval::NS) {
			seconds += 1;
			nanoseconds -= Interval::NS;
		}
		
		auto flags = out.flags();
		auto fill = out.fill();
		auto width = out.width();
		
		out << seconds << '.' << std::setfill('0') << std::internal << std::setw(9) << nanoseconds;
		
		out.width(width);
		out.fill(fill);
		out.flags(flags);
		
		return out;
	}
}
