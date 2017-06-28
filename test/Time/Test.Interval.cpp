//
//  Test.Interval.cpp
//  This file is part of the "Time" project and released under the MIT License.
//
//  Created by Samuel Williams on 28/6/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#include <UnitTest/UnitTest.hpp>

#include <Time/Interval.hpp>

namespace Time
{
	UnitTest::Suite IntervalTestSuite {
		"Time::Interval",
		
		{"it should measure a time value",
			[](UnitTest::Examiner & examiner) {
				Interval i;
				
				examiner.expect(i) > Interval(0);
			}
		},
		
		{"time is monotonically increasing",
			[](UnitTest::Examiner & examiner) {
				Interval a;
				Interval(0.001).sleep();
				Interval b;
				
				examiner.expect(a) < b;
			}
		},
		
		{"can be compared",
			[](UnitTest::Examiner & examiner) {
				Interval a(1.1), b(2.2), c(3.3);
				
				examiner.expect(a) < b;
				examiner.expect(a) <= a;
				examiner.expect(c) > b;
				examiner.expect(c) >= c;
				examiner.expect(a) == a;
				examiner.expect(b) != a;
			}
		},
		
		{"can be subtracted precisely",
			[](UnitTest::Examiner & examiner) {
				Interval a({1, 1}), b({2, 2}), c({3, 1});
				
				// The reason for this unusal result is that it's the same as {-1, -1}.
				// But we prefer if the right hand side is not negative in any case.
				
				auto ab = a - b;
				examiner.expect(ab) == Interval({-2, 999999999});
				
				auto abb = ab + b;
				examiner.expect(abb) == a;
				
				auto cb = c - b;
				examiner.expect(cb) == Interval({0, 999999999});
			}
		},
	};
}
