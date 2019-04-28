************
Gtest Basics
************

**TERM**

+------------------+--------------------------------------------------------------------------------------+
| Google Test Term | Meaning                                                                              |
+==================+======================================================================================+
| TEST()           | Exercise a particular program path with specific input values and verify the results |
+------------------+--------------------------------------------------------------------------------------+
| Test Case        | A set of several tests related to one component                                      |
+------------------+--------------------------------------------------------------------------------------+

**FRAME WORK**

Typical Usage::

   #include "gtest/gtest.h"
   
   TEST(SquareRootTest, PositiveNos)
   {
      EXPECT_EQ(18.0, square - root(324.0));
      EXPECT_EQ(25.4, square - root(645.16));
      EXPECT_EQ(50.3321, square - root(2533.310224));
   }
   
   TEST(SquareRootTest, ZeroAndNegativeNos)
   {
      ASSERT_EQ(0.0, square - root(0.0));
      ASSERT_EQ(-1, square - root(-22.0));
   }
   
   int main(int argc, char **argv)
   {
      ::testing::InitGoogleTest(&argc, argv);
      return RUN_ALL_TESTS();
   }

The ``::testing::InitGoogleTest`` method initializes the framework
and must be called before ``RUN_ALL_TESTS``. ``RUN_ALL_TESTS`` must
be called only once in the code because multiple calls to it conflict
with some of the advanced features of the framework and, therefore,
are not supported. Note that ``RUN_ALL_TESTS`` automatically detects
and runs all the tests defined using the ``TEST`` macro. By default,
the results are printed to standard output.


**CMDLINE SWITHCHES**

Test Selection::

   --gtest_list_tests
      List the names of all tests instead of running them. The name of
      TEST(Foo, Bar) is "Foo.Bar".
   
   --gtest_filter=POSTIVE_PATTERNS[-NEGATIVE_PATTERNS]
      Run only the tests whose name matches one of the positive patterns but
      none of the negative patterns. '?' matches any single character; '*'
      matches any substring; ':' separates two patterns.
   
   --gtest_also_run_full_tests
      Run all tests.
   
   --gtest_also_run_disabled_tests
      Run all disabled tests too.

Test Execution::

   --gtest_repeat=[COUNT]
      Run the tests repeatedly; use a negative count to repeat forever.
   
   --gtest_shuffle
      Randomize tests' orders on every iteration.

   --gtest_random_seed=[NUMBER]
      Random number seed to use for shuffling test orders (between 1 and
      99999, or 0 to use a seed based on the current time).

Test Output::

   --gtest_color=(yes|no|auto)
      Enable/disable colored output. The default is auto.
   
   --gtest_print_time=0
      Don't print the elapsed time of each test.
   
   --gtest_output=xml[:DIRECTORY_PATH\|:FILE_PATH]
      Generate an XML report in the given directory or with the given file
      name. FILE_PATH defaults to test_details.xml.

Assertion Behavior::

   --gtest_break_on_failure
      Turn assertion failures into debugger break-points.
   
   --gtest_throw_on_failure
      Turn assertion failures into C++ exceptions.
   
   --gtest_catch_exceptions=0
      Do not report exceptions as test failures. Instead, allow them
      to crash the program or throw a pop-up (on Windows).

Skip certain tests::

   add DISABLED_ before the test you wish to skip.
   for example, change TEST_F(AutomationCarTester, inhibitSAutoSleep)
   to TEST_F(AutomationCarTester, DISABLED_inhibitSAutoSleep) to skip
   AutomationCarTester.inhibitSAutoSleep test.

.. code-block:: bash

   # run TripRecorderTest.case* except TripRecorderTest.case6
   --gtest_filter=TripRecorderTest.case*:-TripRecorderTest.case6


**ASSERT MACROS**

.. code-block:: c++

   ASSERT_EQ(expected, actual)
   ASSERT_NE(expected, actual)
   ASSERT_NEAR(expected, actual, absolute_range)
   
   EXPECT_EQ(expected, actual)
   EXPECT_TRUE(condition)
   EXPECT_FALSE(condition)
   
   ASSERT_FLOAT_EQ(expected, actual)
   ASSERT_DOUBLE_EQ(expected, actual)
   ASSERT_NEAR(expected, actual, absolute_range)
   
   EXPECT_FLOAT_EQ(expected, actual)
   EXPECT_DOUBLE_EQ(expected, actual)
   EXPECT_NEAR(expected, actual, absolute_range)
   
   // the two C strings have the same content
   ASSERT_STREQ(str1, str2)
   EXPECT_STREQ(str1, str2) 
   // the two C strings have different content
   ASSERT_STRNE(str1, str2)
   EXPECT_STRNE(str1, str2) 
   // the two C strings have the same content, ignoring case
   ASSERT_STRCASEEQ(str1, str2)
   EXPECT_STRCASEEQ(str1, str2)
   // the two C strings have different content, ignoring case
   ASSERT_STRCASENE(str1, str2)
   EXPECT_STRCASENE(str1, str2) 
   
   ASSERT_DEATH(statement, expected_message)
   ASSERT_EXIT(statement, predicate, expected_message)


**TEST FIXTURE**

A test fixture is a place to hold objects and functions shared by
all tests in a test case.  Using a test fixture avoids duplicating
the test code necessary to initialize and cleanup those common
objects for each test.  It is also useful for defining sub-routines
that your tests need to invoke a lot.

The tests share the test fixture in the sense of code sharing, not
data sharing.  Each test is given its own fresh copy of the
fixture.  You cannot expect the data modified by one test to be
passed on to another test, which is a bad idea.

The reason for this design is that tests should be independent and
repeatable.  In particular, a test should not fail as the result of
another test's failure.  If one test depends on info produced by
another test, then the two tests should really be one big test.

The macros for indicating the success/failure of a test
(EXPECT_TRUE, FAIL, etc) need to know what the current test is
(when Google Test prints the test result, it tells you which test
each failure belongs to).  Technically, these macros invoke a
member function of the Test class.  Therefore, you cannot use them
in a global function.  That's why you should put test sub-routines
in a test fixture.

When you define a test fixture, you specify the name of the test
case that will use this fixture. Therefore, a test fixture can
be used by only one test case.

Sometimes, more than one test cases may want to use the same or
slightly different test fixtures. For example, you may want to
make sure that all tests for a GUI library don't leak important
system resources like fonts and brushes. In Google Test, you do
this by putting the shared logic in a super (as in "super class")
test fixture, and then have each test case use a fixture derived
from this super fixture.
