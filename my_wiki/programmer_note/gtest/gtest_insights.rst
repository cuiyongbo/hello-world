Google Test Insights
====================

:class:`::testing::Test`
------------------------

.. code-block:: c++

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
     // test in test case Foo.  Hence a sub-class can define its own
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
   
     // Deletes self.  We deliberately pick an unusual name for this
     // internal method to avoid clashing with names used in user TESTs.
     void DeleteSelf_() { delete this; }
   
     // ...
   };


A test fixture can be viewed as an intergerated test for a specific module. It allows user to customize 
a specific test. A fixture class should inherit itself from the ``::testing::Test`` class and the specific
class module class that it is going to test. Note that it uses the ``TEST_F`` macro instead of ``TEST``. and
Like ``TEST()``, the first argument is the test case name, but for ``TEST_F()`` this must be the name of the
test fixture class.

For each test defined with TEST_F(), Google Test will:

    #. Create a fresh test fixture at runtime.
    #. Immediately initialize it via ``SetUp()``.
    #. Run the test.
    #. Clean up by calling ``TearDown()``.
    #. Delete the test fixture. Note that different
       tests in the same test case have different test
       fixture objects, and Google Test always deletes
       a test fixture before it creates the next one.
       Google Test does not reuse the same test fixture
       for multiple tests. Any changes one test makes
       to the fixture do not affect other tests.

