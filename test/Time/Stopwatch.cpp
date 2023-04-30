//
//  Test.Stopwatch.cpp
//  This file is part of the "Time" project and released under the MIT License.
//
//  Created by Samuel Williams on 28/6/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#include <UnitTest/UnitTest.hpp>

#include <Time/Stopwatch.hpp>

namespace Time
{
	UnitTest::Suite StopwatchTestSuite {
		"Time::Stopwatch",
		
		{"it can measure time",
			[](UnitTest::Examiner & examiner) {
				auto iota = Interval(0, 1);
				Stopwatch stopwatch;
				
				examiner.expect(stopwatch.time()) == Interval(0);
				
				stopwatch.start();
				
				Interval(0, 1).sleep();
				
				auto duration = stopwatch.stop();
				examiner.expect(duration) >= iota;
				
				examiner.expect(stopwatch.time()) == duration;
				examiner.expect(stopwatch.time()) >= iota;
			}
		},
	};
}
