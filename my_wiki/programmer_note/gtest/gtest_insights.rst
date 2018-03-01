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
     // SetUpTestCase() method to shadow the one defined in the super
     // class.
     static void SetUpTestCase() {}
   
     // Tears down the stuff shared by all tests in this test case.
     //
     // Google Test will call Foo::TearDownTestCase() after running the last
     // test in test case Foo.  Hence a sub-class can define its own
     // TearDownTestCase() method to shadow the one defined in the super
     // class.
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