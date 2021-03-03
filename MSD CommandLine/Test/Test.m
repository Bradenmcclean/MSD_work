

#import <XCTest/XCTest.h>
#include "Run.h"
@interface test : XCTestCase
@end
@implementation test
- (void)testAll
{
 if (!run_tests())
 XCTFail(@"failed");
}
@end
