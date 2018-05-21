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
