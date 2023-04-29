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
	class Scheduler
	{
	public:
		typedef std::function<void ()> Callback;
		
		class Handle;
		
		struct Event
		{
			Handle *handle;
			Interval interval;
			
			Event(Handle * handle_, const Interval & interval_) : handle(handle_), interval(interval_) {}
		};
		
		class Handle
		{
			Scheduler & _scheduler;
			Callback _callback;
			std::shared_ptr<Event> _event;
			
		public:
			Handle(Scheduler & scheduler, Callback callback) : _scheduler(scheduler), _callback(callback) {}
			
			~Handle()
			{
				cancel();
			}
			
			void trigger()
			{
				_callback();
			}
			
			void cancel()
			{
				if (_event) {
					_event->handle = nullptr;
					_event.reset();
				}
			}
			
			void schedule(const Interval & interval)
			{
				if (!_event) {
					_event = std::make_shared<Event>(this, interval);
				}
				
				_scheduler.schedule(_event);
			}
			
			void reschedule(const Interval & interval)
			{
				cancel();
				schedule(interval);
			}
		};
		
		void schedule(std::shared_ptr<Event> event)
		{
			_events.push(event);
		}
		
		bool empty() const noexcept
		{
			return _events.empty();
		}
		
		std::optional<Interval> delta()
		{
			while (!_events.empty()) {
				auto event = _events.top();
				
				if (event->handle) {
					return event->interval - Interval(_clock);
				} else {
					_events.pop();
				}
			}
			
			return {};
		}
		
		void run(const Interval & now)
		{
			while (!_events.empty()) {
				auto event = _events.top();
				
				if (event->interval > now)
					break;
				
				_events.pop();
				
				if (event->handle)
					event->handle->trigger();
			}
		}
		
		void run()
		{
			run(Interval(_clock));
		}
		
	protected:
		using SharedEvent = std::shared_ptr<Event>;
		
		struct CompareEvent
		{
			bool operator()(const SharedEvent & a, const SharedEvent & b) const noexcept
			{
				return a->interval > b->interval;
			}
		};
		
		Clock _clock = Clock::MONOTONIC;
		std::priority_queue<SharedEvent, std::vector<SharedEvent>, CompareEvent> _events;
	};
}