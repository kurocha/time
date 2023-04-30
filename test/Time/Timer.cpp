//
//  Test.Timer.cpp
//  This file is part of the "Time" project and released under the MIT License.
//
//  Created by Samuel Williams on 28/6/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#include <UnitTest/UnitTest.hpp>

#include <Time/Timer.hpp>

namespace Time
{
	UnitTest::Suite TimerTestSuite {
		"Time::Timer",
		
		{"it can measure time incrementally",
			[](UnitTest::Examiner & examiner) {
				Timer timer;
				
				Interval({0, 1}).sleep();
				
				examiner.expect(timer.time()) > Interval(0);
			}
		},
	};
}
