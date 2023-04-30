//
//  Test.Timeout.cpp
//  This file is part of the "Time" project and released under the MIT License.
//
//  Created by Samuel Williams on 28/6/2017.
//  Copyright, 2017, by Samuel Williams. All rights reserved.
//

#include <UnitTest/UnitTest.hpp>

#include <Time/Timeout.hpp>

namespace Time
{
	UnitTest::Suite TimeoutTestSuite {
		"Time::Timeout",
		
		{"it can expire",
			[](UnitTest::Examiner & examiner) {
				Duration iota(0, 1);
				Timeout timeout(iota);
				
				examiner.expect(timeout.expired()) == false;
				
				timeout.start();
				iota.sleep();
				
				examiner.expect(timeout.expired()) == true;
			}
		},
	};
}
