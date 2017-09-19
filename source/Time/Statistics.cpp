//
//  Statistics.cpp
//  File file is part of the "Time" project and released under the MIT License.
//
//  Created by Samuel Williams on 28/6/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#include "Statistics.hpp"

#include <algorithm>

namespace Time
{
	Statistics::Statistics()
	{
	}
	
	Statistics & Statistics::operator+=(const Statistics & other) noexcept
	{
		if (other._count > 0) {
			if (_count > 0) {
				_min = std::min(_min, other._min);
				_max = std::max(_max, other._max);
				
				_count += other._count;
				_duration += other._duration;
			} else {
				_min = other._min;
				_max = other._max;
				
				_count = other._count;
				_duration = other._duration;
			}
		}
		
		return *this;
	}
	
	Interval Statistics::average_duration() const noexcept
	{
		if (_count == 0) return 0;

		return static_cast<double>(_duration) / _count;
	}
	
	double Statistics::updates_per_second() const noexcept
	{
		double duration = _duration;
		
		if (duration == 0) return 0;

		return _count / duration;
	}
	
	double Statistics::amortized_updates_per_second(const Time::Interval & duration) const noexcept
	{
		if (_count > 0) {
			double amortized_average_time = duration / _count;
			return 1.0 / amortized_average_time;
		} else {
			return 0;
		}
	}

	void Statistics::add(const Interval & duration) noexcept
	{
		if (_count == 0) {
			_min = duration;
			_max = duration;
		} else {
			_min = std::min(_min, duration);
			_max = std::max(_max, duration);
		}
		
		_duration += duration;
		_count += 1;
	}
	
	void Statistics::add(Timer & timer) noexcept
	{
		add(timer.time());
		timer.reset();
	}
}
