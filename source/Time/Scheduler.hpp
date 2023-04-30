//
//  Interval.hpp
//  File file is part of the "Time" project and released under the MIT License.
//
//  Created by Samuel Williams on 29/4/2023.
//  Copyright, 2023, by Samuel Williams. All rights reserved.
//

#pragma once

#include "Interval.hpp"

#include <functional>
#include <queue>
#include <optional>
#include <memory>

namespace Time
{
	template <typename Handle>
	class Scheduler
	{
	public:
		struct Event
		{
			Interval interval;
			Handle handle;
			
			Event(const Interval & interval_, const Handle & handle_) : interval(interval_), handle(handle_) {}
			
			bool operator<(const Event & other) const noexcept
			{
				return interval > other.interval;
			}
		};
		
		using EventReference = std::shared_ptr<Event>;
		struct EventReferenceCompare
		{
			bool operator()(const EventReference & a, const EventReference & b) const noexcept
			{
				return *a < *b;
			}
		};
		
		EventReference schedule(const Interval & interval, Handle & handle)
		{
			auto reference = std::make_shared<Event>(interval, handle);
			
			_events.push(reference);
			
			return reference;
		}
		
		bool empty() const noexcept
		{
			return _events.empty();
		}
		
		std::optional<Interval> delta() const
		{
			while (!_events.empty()) {
				auto & event = _events.top();
				
				if (event->handle) {
					return event->interval;
				} else {
					_events.pop();
				}
			}
			
			return std::nullopt;
		}
		
		bool waiting() const
		{
			return static_cast<bool>(delta());
		}
		
		void run(const Interval & now)
		{
			while (!_events.empty()) {
				auto event = _events.top();
				
				if (event->interval > now)
					break;
				
				_events.pop();
				
				event->handle();
			}
		}
		
		Interval now() const noexcept
		{
			return Interval(_clock);
		}
		
		void run()
		{
			run(now());
		}
		
	protected:
		Clock _clock = Clock::MONOTONIC;
		
		mutable std::priority_queue<EventReference, std::vector<EventReference>, EventReferenceCompare> _events;
	};
}