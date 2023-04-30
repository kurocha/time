//
//  Duration.cpp
//  This file is part of the "Time" project and released under the MIT License.
//
//  Created by Samuel Williams on 30/4/2023.
//  Copyright, 2023, by Samuel Williams. All rights reserved.
//

#include <UnitTest/UnitTest.hpp>

#include <Time/Interval.hpp>

namespace Time
{
	using namespace UnitTest::Expectations;
	
	UnitTest::Suite DurationTestSuite {
		"Time::Duration",
		
		{"it can construct a duration from a timestamp",
			[](UnitTest::Examiner & examiner) {
				Timestamp now;
				
				Duration duration(now);
				examiner.expect(duration).to(be >= Duration(0.0));
			}
		},
	};
}
