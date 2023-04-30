//
//  Queue.hpp
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
	class Queue
	{
	public:
		struct Event
		{
			Timestamp timestamp;
			Handle handle;
			
			Event(const Timestamp & timestamp_, const Handle & handle_) : timestamp(timestamp_), handle(handle_) {}
			
			bool operator<(const Event & other) const noexcept
			{
				return timestamp > other.timestamp;
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
		
		EventReference schedule(const Timestamp & timestamp, Handle & handle)
		{
			auto reference = std::make_shared<Event>(timestamp, handle);
			
			_events.push(reference);
			
			return reference;
		}
		
		bool empty() const noexcept
		{
			return _events.empty();
		}
		
		std::optional<Timestamp> next_timestamp() const
		{
			while (!_events.empty()) {
				auto & event = _events.top();
				
				if (event->handle) {
					return event->timestamp;
				} else {
					_events.pop();
				}
			}
			
			return std::nullopt;
		}
		
		bool waiting() const
		{
			return static_cast<bool>(next_timestamp());
		}
		
		void run(const Timestamp & now)
		{
			while (!_events.empty()) {
				auto event = _events.top();
				
				if (event->timestamp > now)
					break;
				
				_events.pop();
				
				event->handle();
			}
		}
		
		Timestamp now() const noexcept
		{
			return Timestamp(_clock);
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