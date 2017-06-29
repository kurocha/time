//
//  Interval.hpp
//  File file is part of the "Time" project and released under the MIT License.
//
//  Created by Samuel Williams on 28/6/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#pragma once

#include <cstdint>
#include <time.h>

#include <iosfwd>

namespace Time
{
	enum class Clock : int {
		// System-wide realtime clock. Setting this clock requires appropriate privileges.
		REALTIME = CLOCK_REALTIME,
		// Clock that cannot be set and represents monotonic time since some unspecified starting point.
		MONOTONIC = CLOCK_MONOTONIC,
		// High-resolution per-process timer from the CPU.
		PROCESS = CLOCK_PROCESS_CPUTIME_ID,
		// Thread-specific CPU-time clock.
		THREAD = CLOCK_THREAD_CPUTIME_ID,
	};
	
	class Interval
	{
	public:
		typedef struct timespec TimeT;
		static constexpr std::uint64_t NS = 1000*1000*1000;
		
		Interval(const Clock & clock = Clock::MONOTONIC) noexcept
		{
			clock_gettime((clockid_t)clock, &_value);
		}
		
		Interval(const TimeT & value) noexcept : _value(value) {}
		
		Interval(int seconds) noexcept : Interval({seconds, 0}) {}
		Interval(double seconds) noexcept;
		
		const TimeT & as_timespec() const noexcept {return _value;}
		
		operator double() const noexcept
		{
			return static_cast<double>(_value.tv_sec) + static_cast<double>(_value.tv_nsec) / NS;
		}
		
		void sleep() noexcept;
		
		Interval operator-() const noexcept
		{
			return Interval({_value.tv_sec * -1, _value.tv_nsec});
		}
		
		Interval operator-(const Interval & other) const noexcept
		{
			auto & a = _value;
			auto & b = other._value;
			
			auto seconds = a.tv_sec - b.tv_sec;
			auto nanoseconds = a.tv_nsec - b.tv_nsec;
			
			if (nanoseconds < 0) {
				seconds -= 1;
				nanoseconds += NS;
			}
			
			return TimeT{seconds, nanoseconds};
		}
		
		Interval & operator-=(const Interval & other) noexcept
		{
			return ((*this) = (*this) - other);
		}
		
		Interval operator+(const Interval & other) const noexcept
		{
			auto & a = _value;
			auto & b = other._value;
			
			auto seconds = a.tv_sec + b.tv_sec;
			auto nanoseconds = a.tv_nsec + b.tv_nsec;
			
			if (nanoseconds > NS) {
				seconds += 1;
				nanoseconds -= NS;
			}
			
			return TimeT{seconds, nanoseconds};
		}
		
		Interval & operator+=(const Interval & other) noexcept
		{
			return ((*this) = (*this) + other);
		}
		
		bool operator==(const Interval & other) const noexcept
		{
			auto & a = _value;
			auto & b = other._value;
			
			return a.tv_sec == b.tv_sec && a.tv_nsec == b.tv_nsec;
		}
		
		bool operator!=(const Interval & other) const noexcept
		{
			auto & a = _value;
			auto & b = other._value;
			
			return a.tv_sec != b.tv_sec || a.tv_nsec != b.tv_nsec;
		}
		
		bool operator<(const Interval & other) const noexcept
		{
			auto & a = _value;
			auto & b = other._value;
			
			if (a.tv_sec < b.tv_sec) {
				return true;
			} else if (a.tv_sec == b.tv_sec && a.tv_nsec < b.tv_nsec) {
				return true;
			} else {
				return false;
			}
		}
		
		bool operator<=(const Interval & other) const noexcept
		{
			auto & a = _value;
			auto & b = other._value;
			
			if (a.tv_sec < b.tv_sec) {
				return true;
			} else if (a.tv_sec == b.tv_sec && a.tv_nsec <= b.tv_nsec) {
				return true;
			} else {
				return false;
			}
		}
		
		bool operator>(const Interval & other) const noexcept
		{
			auto & a = _value;
			auto & b = other._value;
			
			if (a.tv_sec > b.tv_sec) {
				return true;
			} else if (a.tv_sec == b.tv_sec && a.tv_nsec > b.tv_nsec) {
				return true;
			} else {
				return false;
			}
		}
		
		bool operator>=(const Interval & other) const noexcept
		{
			auto & a = _value;
			auto & b = other._value;
			
			if (a.tv_sec > b.tv_sec) {
				return true;
			} else if (a.tv_sec == b.tv_sec && a.tv_nsec >= b.tv_nsec) {
				return true;
			} else {
				return false;
			}
		}
		
		const TimeT & value() const noexcept {return _value;}
		const int64_t seconds() const noexcept {return _value.tv_sec;}
		const int64_t nanoseconds() const noexcept {return _value.tv_nsec;}
		
	private:
		TimeT _value = {0, 0};
	};
	
	std::ostream & operator<<(std::ostream & out, const Interval & interval);
}
