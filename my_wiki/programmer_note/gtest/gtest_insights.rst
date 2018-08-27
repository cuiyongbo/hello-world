********************
Google Test Insights
********************

Frame insights
==============

.. code-block:: cpp
   :caption: Initializers

   // Initializes Google Test.  This must be called before calling
   // RUN_ALL_TESTS(). In particular, it parses a command line for the
   // flags that Google Test recognizes.  Whenever a Google Test flag is
   // seen, it is removed from argv, and *argc is decremented.
   //
   // No value is returned. Instead, the Google Test flag variables are
   // updated.
   //
   // Calling the function for the second time has no user-visible effect.
   GTEST_API_ void InitGoogleTest(int* argc, char** argv);
   
   // Use this function in main() to run all tests. It returns 0 if all
   // tests are successful, or 1 otherwise.
   //
   // RUN_ALL_TESTS() should be invoked after the command line has been
   // parsed by InitGoogleTest().
   //
   // This function was formerly a macro; thus, it is in the global
   // namespace and has an all-caps name.
   int RUN_ALL_TESTS() GTEST_MUST_USE_RESULT_;
   
   inline int RUN_ALL_TESTS() {
     return ::testing::UnitTest::GetInstance()->Run();
   }

.. code-block:: cpp
   :caption: Test frame class

   class GTEST_API_ Test {
   public:
   
      // Sets up the stuff shared by all tests in this test case.
      //
      // Google Test will call Foo::SetUpTestCase() before running the first
      // test in test case Foo.  Hence a sub-class can define its own
      // SetUpTestCase() method to shadow the one defined in the super class.
      static void SetUpTestCase() {}
   
      // Tears down the stuff shared by all tests in this test case.
      //
      // Google Test will call Foo::TearDownTestCase() after running the last
      // test in test case Foo. Hence a sub-class can define its own
      // TearDownTestCase() method to shadow the one defined in the super class.
      static void TearDownTestCase() {}
   
      // ...
   
   protected:
   
      // Sets up the test fixture.
      virtual void SetUp();
   
      // Tears down the test fixture.
      virtual void TearDown();
   
      // ...
   
   private:
   
      // Sets up, executes, and tears down the test.
      void Run();
   
      // Deletes self. We deliberately pick an unusual name for this
      // internal method to avoid clashing with names used in user TESTs.
      void DeleteSelf_() { delete this; }
   
      // ...
   };


.. code-block:: cpp
   :caption: Test case macro

   namespace ::testing {

      // ...

      // Defines a test.
      //
      // The first parameter is the name of the test case, and the second
      // parameter is the name of the test within the test case.
      //
      // The convention is to end the test case name with "Test". For
      // example, a test case for the Foo class can be named FooTest.
      //
      // The user should put his test code between braces after using this
      // macro. Example:
      //
      //   TEST(FooTest, InitializesCorrectly) {
      //     Foo foo;
      //     EXPECT_TRUE(foo.StatusIsOK());
      //   }
      
      // Note that we call GetTestTypeId() instead of GetTypeId<
      // ::testing::Test>() here to get the type ID of testing::Test. This
      // is to work around a suspected linker bug when using Google Test as
      // a framework on Mac OS X.  The bug causes GetTypeId<
      // ::testing::Test>() to return different values depending on whether
      // the call is from the Google Test framework itself or from user test
      // code. GetTestTypeId() is guaranteed to always return the same
      // value, as it always calls GetTypeId<>() from the Google Test
      // framework.
      #define GTEST_TEST(test_case_name, test_name)\
        GTEST_TEST_(test_case_name, test_name, \
                    ::testing::Test, ::testing::internal::GetTestTypeId())
      
      // Define this macro to 1 to omit the definition of TEST(), which
      // is a generic name and clashes with some other libraries.
      #if !GTEST_DONT_DEFINE_TEST
      # define TEST(test_case_name, test_name) GTEST_TEST(test_case_name, test_name)
      #endif
      
      // Defines a test that uses a test fixture.
      //
      // The first parameter is the name of the test fixture class, which
      // also doubles as the test case name. The second parameter is the
      // name of the test within the test case.
      //
      // A test fixture class must be declared earlier. The user should put
      // his test code between braces after using this macro. Example:
      //
      //   class FooTest : public testing::Test {
      //    protected:
      //     virtual void SetUp() { b_.AddElement(3); }
      //
      //     Foo a_;
      //     Foo b_;
      //   };
      //
      //   TEST_F(FooTest, InitializesCorrectly) {
      //     EXPECT_TRUE(a_.StatusIsOK());
      //   }
      //
      //   TEST_F(FooTest, ReturnsElementCountCorrectly) {
      //     EXPECT_EQ(0, a_.size());
      //     EXPECT_EQ(1, b_.size());
      //   }
      
      #define TEST_F(test_fixture, test_name)\
        GTEST_TEST_(test_fixture, test_name, test_fixture, \
                    ::testing::internal::GetTypeId<test_fixture>())

      // ...
      
   }
      
Samples
=======

.. toctree::
   :titlesonly:

   gtest_type_parameterized_tests
   gtest_value_parameterized_tests
   gtest_combine_tests
   gtest_listener_api
   gtest_memory_leak_checker

