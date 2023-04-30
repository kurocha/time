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
		static constexpr std::int64_t NS = 1000*1000*1000;
		static constexpr std::int64_t MS = 1000;
		
		Interval(const Clock & clock = Clock::MONOTONIC) noexcept
		{
			clock_gettime((clockid_t)clock, &_value);
		}
		
		Interval(const TimeT & value) noexcept : _value(value) {}
		
		Interval(int seconds) noexcept : Interval({seconds, 0}) {}
		Interval(double seconds) noexcept;
		
		static Interval from_nanoseconds(std::uint64_t nanoseconds)
		{
			TimeT time;
			
			time.tv_sec = nanoseconds / NS;
			time.tv_nsec = nanoseconds - (time.tv_sec * NS);
			
			return Interval(time);
		}
		
		static Interval from_milliseconds(std::uint64_t milliseconds)
		{
			TimeT time;
			
			time.tv_sec = milliseconds / MS;
			time.tv_nsec = (milliseconds - time.tv_sec * MS) * 1000000;
			
			return Interval(time);
		}
		
		const TimeT & as_timespec() const noexcept {return _value;}
		std::int64_t as_nanoseconds() const noexcept {return _value.tv_sec*NS + _value.tv_nsec;}
		std::int64_t as_milliseconds() const noexcept {return _value.tv_sec*MS + _value.tv_nsec/(NS/MS);}
		double as_seconds() const noexcept {return static_cast<double>(_value.tv_sec) + static_cast<double>(_value.tv_nsec) / NS;}
		
		operator double() const noexcept
		{
			return as_seconds();
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
		
		std::int64_t seconds() const noexcept {return _value.tv_sec;}
		std::int64_t nanoseconds() const noexcept {return _value.tv_nsec;}
		
	private:
		TimeT _value = {0, 0};
	};
	
	std::ostream & operator<<(std::ostream & out, const Interval & interval);
	
	class Timestamp;
	
	// A duration is a relative point in time.
	class Duration : public Interval
	{
	public:
		Duration() : Interval(0) {}
		explicit Duration(const Interval & interval) : Interval(interval) {}
		
		Duration(const Timestamp & timestamp, Clock clock = Clock::MONOTONIC);
		
		Duration operator+(const Duration & other) const noexcept
		{
			return Duration(Interval::operator+(other));
		}
		
		Duration operator-(const Duration & other) const noexcept
		{
			return Duration(Interval::operator-(other));
		}
		
		Duration & operator+=(const Duration & other) noexcept
		{
			return ((*this) = (*this) + other);
		}
		
		Duration & operator-=(const Duration & other) noexcept
		{
			return ((*this) = (*this) - other);
		}
		
		Timestamp operator+(const Timestamp & timestamp) const noexcept;
	};
	
	// A timestamp is an absolute point in time.
	class Timestamp : public Interval
	{
	public:
		Timestamp(const Clock & clock = Clock::MONOTONIC) : Interval(clock) {}
		explicit Timestamp(const Interval & interval) : Interval(interval) {}
		
		// Construct an absolute time relative to now().
		Timestamp(const Duration & duration, Clock clock = Clock::MONOTONIC) : Interval(Interval(clock) + duration) {}
		
		Timestamp operator+(const Duration & duration) const noexcept
		{
			return Timestamp(Interval::operator+(duration));
		}
		
		Timestamp operator-(const Duration & duration) const noexcept
		{
			return Timestamp(Interval::operator-(duration));
		}
		
		Timestamp & operator+=(const Duration & duration) noexcept
		{
			return ((*this) = (*this) + duration);
		}
		
		Timestamp & operator-=(const Duration & duration) noexcept
		{
			return ((*this) = (*this) - duration);
		}
		
		Duration operator-(const Timestamp & other) const noexcept
		{
			return Duration(Interval::operator-(other));
		}
	};
	
	inline Duration::Duration(const Timestamp & timestamp, Clock clock) : Interval(timestamp - Timestamp(clock)) {}
	
	inline Timestamp Duration::operator+(const Timestamp & timestamp) const noexcept
	{
		return Timestamp(Interval::operator+(timestamp));
	}
}
