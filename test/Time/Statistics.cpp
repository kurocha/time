//
//  Test.Statistics.cpp
//  This file is part of the "Time" project and released under the MIT License.
//
//  Created by Samuel Williams on 28/6/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#include <UnitTest/UnitTest.hpp>

#include <Time/Statistics.hpp>

namespace Time
{
	UnitTest::Suite StatisticsTestSuite {
		"Time::Statistics",
		
		{"it defaults to zero",
			[](UnitTest::Examiner & examiner) {
				Statistics statistics;
				
				examiner.expect(statistics.count()) == 0u;
				examiner.expect(statistics.average_duration()) == Interval(0);
				examiner.expect(statistics.minimum_duration()) == Interval(0);
				examiner.expect(statistics.maximum_duration()) == Interval(0);
			}
		},
		
		{"it can compute min, max and average",
			[](UnitTest::Examiner & examiner) {
				Statistics statistics;
				
				statistics.add(1);
				statistics.add(2);
				statistics.add(3);
				
				examiner.expect(statistics.count()) == 3u;
				examiner.expect(statistics.average_duration()) == Interval(2.0);
				examiner.expect(statistics.minimum_duration()) == Interval(1);
				examiner.expect(statistics.maximum_duration()) == Interval(3);
			}
		},
		
		{"it can merge statistics",
			[](UnitTest::Examiner & examiner) {
				Statistics a, b;
				
				a.add(2);
				a.add(4);
				b.add(6);
				b.add(8);
				
				a += b;
				
				examiner.expect(a.count()) == 4u;
				examiner.expect(a.average_duration()) == Interval(5.0);
				examiner.expect(a.minimum_duration()) == Interval(2);
				examiner.expect(a.maximum_duration()) == Interval(8);
			}
		},
	};
}
