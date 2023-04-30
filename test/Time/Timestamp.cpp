//
//  Timestamp.cpp
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
	
	UnitTest::Suite TimestampTestSuite {
		"Time::Timestamp",
		
		{"it can convert relative duration into absolute timestamp",
			[](UnitTest::Examiner & examiner) {
				Timestamp now;
				
				Duration duration(1.0);
				examiner.expect(duration.as_seconds()).to(be == 1.0);
				
				Timestamp timestamp(duration);
				examiner.expect(timestamp).to(be >= now);
			}
		},
	};
}
