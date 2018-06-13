*********************************
unittest — Unit testing framework
*********************************

Basic Concepts
==============

The Python unit testing framework, sometimes referred to as “PyUnit,” 
is a Python language version of JUnit, by Kent Beck and Erich Gamma. 
JUnit is, in turn, a Java version of Kent’s Smalltalk testing framework. 
Each is the de facto standard unit testing framework for its respective language.

unittest supports test automation, sharing of setup and shutdown code for tests, 
aggregation of tests into collections, and independence of the tests from the reporting 
framework. The unittest module provides classes that make it easy to support these qualities 
for a set of tests.

To achieve this, unittest supports some important concepts::

   test fixture
   A test fixture represents the preparation needed to perform one or more tests, 
   and any associate cleanup actions. This may involve, for example, creating temporary 
   or proxy databases, directories, or starting a server process.

   test case
   A test case is the smallest unit of testing. It checks for a specific response 
   to a particular set of inputs. unittest provides a base class, TestCase, which 
   may be used to create new test cases.

   test suite
   A test suite is a collection of test cases, test suites, or both. It is used 
   to aggregate tests that should be executed together.

   test runner
   A test runner is a component which orchestrates the execution of tests and provides 
   the outcome to the user. The runner may use a graphical interface, a textual interface, 
   or return a special value to indicate the results of executing the tests.

The test case and test fixture concepts are supported through the :class:`TestCase` and :class:`FunctionTestCase` 
classes; the former should be used when creating new tests, and the latter can be used when integrating existing 
test code with a unittest-driven framework. When building test fixtures using :class:`TestCase`, the *setUp()* 
and *tearDown()* methods can be overridden to provide initialization and cleanup for the fixture. 
With :class:`FunctionTestCase`, existing functions can be passed to the constructor for these purposes. 
When the test is run, the fixture initialization is run first; if it succeeds, the cleanup method is run 
after the test has been executed, regardless of the outcome of the test. Each instance of the :class:`TestCase` 
will only be used to run a single test method, so a new fixture is created for each test.

Test suites are implemented by the :class:`TestSuite` class. This class allows individual tests and test suites 
to be aggregated; when the suite is executed, all tests added directly to the suite and in “child” test suites 
are run.

A test runner is an object that provides a single method, *run()*, which accepts a :class:`TestCase` or 
:class:`TestSuite` object as a parameter, and returns a result object. The :class:`TestResult` is provided 
for use as the result object. unittest provides the :class:`TextTestRunner` as an example test runner which 
reports test results on the standard error stream by default. Alternate runners can be implemented for other 
environments (such as graphical environments) without any need to derive from a specific class.


Basic Examples
==============

.. code-block:: python

   import unittest
   
   class TestStringMethods(unittest.TestCase):
   
       def test_upper(self):
           self.assertEqual('foo'.upper(), 'FOO')
   
       def test_isupper(self):
           self.assertTrue('FOO'.isupper())
           self.assertFalse('Foo'.isupper())
   
       def test_split(self):
           s = 'hello world'
           self.assertEqual(s.split(), ['hello', 'world'])
           # check that s.split fails when the separator is not a string
           with self.assertRaises(TypeError):
               s.split(2)
   
   if __name__ == '__main__':
       unittest.main()


Instead of ``unittest.main()``, there are other ways to run the tests with a finer level of control, 
less terse output, and no requirement to be run from the command line. For example, the last two 
lines may be replaced with::

   suite = unittest.TestLoader().loadTestsFromTestCase(TestStringMethods)
   unittest.TextTestRunner(verbosity=2).run(suite)


.. note::

   #. run test cases only interested
      
      .. code-block:: python
      
         suite = unittest.TestSuite()
         suite.addTest(Test("test_dynamic_adjustment_no_better_route"))
         suite.addTest(Test("test_dynamic_adjustment_new_better_route"))
         result = unittest.TextTestRunner(verbosity=2).run(suite)
   
   #. run all tests from a test suite
      
      .. code-block:: python
   
         suite = unittest.TestLoader().loadTestsFromTestCase(Test)
         result = unittest.TextTestRunner(verbosity=2).run(suite)


Organizing test code
====================

The basic building blocks of unit testing are test cases — single scenarios 
that must be set up and checked for correctness. In unittest, test cases are 
represented by instances of unittest’s :class:`TestCase` class. To make your 
own test cases you must write subclasses of :class:`TestCase`, 
or use :class:`FunctionTestCase`.

An instance of a TestCase-derived class is an object that can completely run 
a single test method, together with optional set-up and tidy-up code.

The testing code of a :class:`TestCase` instance should be entirely self contained, 
such that it can be run either in isolation or in arbitrary combination with any 
number of other test cases.

The simplest TestCase subclass will simply override the *runTest()* method in order 
to perform specific testing code::

   import unittest
   
   class DefaultWidgetSizeTestCase(unittest.TestCase):
       def runTest(self):
           widget = Widget('The widget')
           self.assertEqual(widget.size(), (50, 50), 'incorrect default size')

**Note** that in order to test something, we use one of the assert*() methods provided 
by the :class:`TestCase` base class. If the test fails, an exception will be raised, 
and unittest will identify the test case as a failure. Any other exceptions will be 
treated as errors. This helps you identify where the problem is: failures are caused 
by incorrect results - a 5 where you expected a 6. Errors are caused by incorrect code.
e.g., a :exc:`TypeError` caused by an incorrect function call.

The way to run a test case will be described later. For now, note that to construct 
an instance of such a test case, we call its constructor without arguments::

   testCase = DefaultWidgetSizeTestCase()

Now, such test cases can be numerous, and their set-up can be repetitive. In the above case, 
constructing a *Widget* in each of 100 Widget test case subclasses would mean unsightly duplication.

Luckily, we can factor out such set-up code by implementing a method called *setUp()*, 
which the testing framework will automatically call for us when we run the test::

   import unittest
   
   class SimpleWidgetTestCase(unittest.TestCase):
       def setUp(self):
           self.widget = Widget('The widget')
   
   class DefaultWidgetSizeTestCase(SimpleWidgetTestCase):
       def runTest(self):
           self.assertEqual(self.widget.size(), (50,50),
                            'incorrect default size')
   
   class WidgetResizeTestCase(SimpleWidgetTestCase):
       def runTest(self):
           self.widget.resize(100,150)
           self.assertEqual(self.widget.size(), (100,150),
                            'wrong size after resize')
   
If the *setUp()* method raises an exception while the test is running, the framework 
will consider the test to have suffered an error, and the *runTest()* method will not 
be executed.

Similarly, we can provide a *tearDown()* method that tidies up after the *runTest()* 
method has been run::

   import unittest
   
   class SimpleWidgetTestCase(unittest.TestCase):
       def setUp(self):
           self.widget = Widget('The widget')
   
       def tearDown(self):
           self.widget.dispose()
           self.widget = None

If *setUp()* succeeded, the *tearDown(*) method will be run whether *runTest()* 
succeeded or not. Such a working environment for the testing code is called a 
**fixture**.

Often, many small test cases will use the same fixture. In this case, we would 
end up subclassing *SimpleWidgetTestCase* into many small one-method classes 
such as *DefaultWidgetSizeTestCase*. This is time-consuming and discouraging, 
so in the same vein as JUnit, unittest provides a simpler mechanism::

   import unittest
   
   class WidgetTestCase(unittest.TestCase):
       def setUp(self):
           self.widget = Widget('The widget')
   
       def tearDown(self):
           self.widget.dispose()
           self.widget = None
   
       def test_default_size(self):
           self.assertEqual(self.widget.size(), (50,50),
                            'incorrect default size')
   
       def test_resize(self):
           self.widget.resize(100,150)
           self.assertEqual(self.widget.size(), (100,150),
                            'wrong size after resize')

Here we have not provided a *runTest()* method, but have instead provided two different test methods. 
Class instances will now each run one of the test_*() methods, with *self.widget* created and destroyed 
separately for each instance. When creating an instance we must specify the test method it is to run. 
We do this by passing the method name in the constructor::

   defaultSizeTestCase = WidgetTestCase('test_default_size')
   resizeTestCase = WidgetTestCase('test_resize')

Test case instances are grouped together according to the features they test. 
unittest provides a mechanism for this: the test suite, represented by unittest’s 
:class:`TestSuite` class::

   widgetTestSuite = unittest.TestSuite()
   widgetTestSuite.addTest(WidgetTestCase('test_default_size'))
   widgetTestSuite.addTest(WidgetTestCase('test_resize'))

For the ease of running tests, as we will see later, it is a good idea to provide 
in each test module a callable object that returns a pre-built test suite::

   def suite():
       suite = unittest.TestSuite()
       suite.addTest(WidgetTestCase('test_default_size'))
       suite.addTest(WidgetTestCase('test_resize'))
       return suite

or even::

   def suite():
      tests = ['test_default_size', 'test_resize']
      return unittest.TestSuite(map(WidgetTestCase, tests))

Since it is a common pattern to create a :class:`TestCase` subclass with many similarly 
named test functions, unittest provides a :class:`TestLoader` class that can be used to 
automate the process of creating a test suite and populating it with individual tests. 
For example,

.. code-block:: python

   suite = unittest.TestLoader().loadTestsFromTestCase(WidgetTestCase)

will create a test suite that will run *WidgetTestCase.test_default_size()* and 
*WidgetTestCase.test_resize*. :class:`TestLoader` uses the 'test' method name prefix to 
identify test methods automatically.

Note that the order in which the various test cases will be run is determined by sorting 
the test function names with respect to the built-in ordering for strings.

Often it is desirable to group suites of test cases together, so as to run tests for the 
whole system at once. This is easy, since :class:`TestSuite` instances can be added to a 
:class:`TestSuite` just as :class:`TestCase` instances can be added to a 
:class:`TestCase`::

   suite1 = module1.TheTestSuite()
   suite2 = module2.TheTestSuite()
   alltests = unittest.TestSuite([suite1, suite2])

You can place the definitions of test cases and test suites in the same modules as the code 
they are to test (such as :file:`widget.py`), but there are several advantages to placing the test 
code in a separate module, such as :file:`test_widget.py`:

   * The test module can be run standalone from the command line.
   * The test code can more easily be separated from shipped code.
   * There is less temptation to change test code to fit the code it tests without a good reason.
   * Test code should be modified much less frequently than the code it tests.
   * Tested code can be refactored more easily.
   * Tests for modules written in C must be in separate modules anyway, so why not be consistent?
   * If the testing strategy changes, there is no need to change the source code.
     

Re-using old test code
======================

Some users will find that they have existing test code that they would like to run from unittest, 
without converting every old test function to a :class:`TestCase` subclass.

For this reason, unittest provides a :class:`FunctionTestCase` class. This subclass of :class:`TestCase` 
can be used to wrap an existing test function. *Set-up* and *tear-down* functions can also be provided.

Given the following test function::

   def testSomething():
       something = makeSomething()
       assert something.name is not None
       # ...

one can create an equivalent test case instance as follows::

   testcase = unittest.FunctionTestCase(testSomething)

If there are additional set-up and tear-down methods that should be called as part of the test case’s operation, 
they can also be provided like so::

   testcase = unittest.FunctionTestCase(testSomething,
                                        setUp=makeSomethingDB,
                                        tearDown=deleteSomethingDB)

To make migrating existing test suites easier, unittest supports tests raising :exc:`AssertionError` to indicate 
test failure. However, it is recommended that you use the explicit ``TestCase.fail*()`` and ``TestCase.assert*()`` 
methods instead, as future versions of unittest may treat :exc:`AssertionError` differently.

.. note::

   Note Even though :class:`FunctionTestCase` can be used to quickly convert an existing test base over to 
   a unittest-based system, this approach is not recommended. Taking the time to set up proper :class:`TestCase` 
   subclasses will make future test refactorings infinitely easier.
   

Skipping tests and expected failures
====================================

Unittest supports skipping individual test methods and even whole classes of tests. 
In addition, it supports marking a test as an **expected failure**, a test that is 
broken and will fail, but shouldn’t be counted as a failure on a :class:`TestResult`.

Skipping a test is simply a matter of using the *skip()* decorator or one of its 
conditional variants.

Basic skipping looks like this::

   class MyTestCase(unittest.TestCase):
   
       @unittest.skip("demonstrating skipping")
       def test_nothing(self):
           self.fail("shouldn't happen")
   
       @unittest.skipIf(mylib.__version__ < (1, 3),
                        "not supported in this library version")
       def test_format(self):
           # Tests that work for only a certain version of the library.
           pass
   
       @unittest.skipUnless(sys.platform.startswith("win"), "requires Windows")
       def test_windows_support(self):
           # windows specific testing code
           pass

Classes can be skipped just like methods::

   @unittest.skip("showing class skipping")
   class MySkippedTestCase(unittest.TestCase):
       def test_not_run(self):
           pass

*TestCase.setUp()* can also skip the test. This is useful when a resource that needs 
to be set up is not available.

Expected failures use the *expectedFailure()* decorator::

   class ExpectedFailureTestCase(unittest.TestCase):
       @unittest.expectedFailure
       def test_fail(self):
           self.assertEqual(1, 0, "broken")

It’s easy to roll your own skipping decorators by making a decorator that calls *skip()* 
on the test when it wants it to be skipped. This decorator skips the test unless the 
passed object has a certain attribute::

   def skipUnlessHasattr(obj, attr):
       if hasattr(obj, attr):
           return lambda func: func
       return unittest.skip("{!r} doesn't have {!r}".format(obj, attr))

The following decorators implement test skipping and expected failures::

   unittest.skip(reason)
   Unconditionally skip the decorated test. reason should describe why 
   the test is being skipped.

   unittest.skipIf(condition, reason)
   Skip the decorated test if condition is true.

   unittest.skipUnless(condition, reason)
   Skip the decorated test unless condition is true.

   unittest.expectedFailure()
   Mark the test as an expected failure. 
   If the test fails when run, the test is not counted as a failure.

   exception unittest.SkipTest(reason)
   This exception is raised to skip a test.

Usually you can use *TestCase.skipTest()* or one of the skipping decorators 
instead of raising this directly.

Skipped tests will not have *setUp()* or *tearDown()* run around them. 
Skipped classes will not have *setUpClass()* or *tearDownClass()* run.


Test cases
==========

.. class:: class unittest.TestCase(methodName='runTest')

   Instances of the TestCase class represent the smallest testable units in the unittest universe. 
   This class is intended to be used as a base class, with specific tests being implemented by 
   concrete subclasses. This class implements the interface needed by the test runner to allow it 
   to drive the test, and methods that the test code can use to check for and report various 
   kinds of failure.
   
   Each instance of TestCase will run a single test method: the method named *methodName*. 
   If you remember, we had an earlier example that went something like this::
      
      def suite():
          suite = unittest.TestSuite()
          suite.addTest(WidgetTestCase('test_default_size'))
          suite.addTest(WidgetTestCase('test_resize'))
          return suite
      
   Here, we create two instances of *WidgetTestCase*, each of which runs a single test.
   
   *methodName* defaults to *runTest()*.
   
   *TestCase* instances provide three groups of methods: one group used to run the test, 
   another used by the test implementation to check conditions and report failures, and 
   some inquiry methods allowing information about the test itself to be gathered.

Methods in the first group (running the test) are:

   .. function:: setUp()

      Method called to prepare the test fixture. 
      This is called immediately before calling the test method; 
      other than :exc:*AssertionError* or *SkipTest*, any exception 
      raised by this method will be considered an error rather than 
      a test failure. The default implementation does nothing.

   .. function:: tearDown()

      Method called immediately after the test method has been called and the result recorded. 
      This is called even if the test method raised an exception, so the implementation in 
      subclasses may need to be particularly careful about checking internal state. Any exception, 
      other than :exc:*AssertionError* or *SkipTest*, raised by this method will be considered an 
      additional error rather than a test failure (thus increasing the total number of reported 
      errors). This method will only be called if the *setUp()* succeeds, regardless of the outcome 
      of the test method. The default implementation does nothing.

   .. function:: setUpClass()
   .. function:: tearDownClass()

      *setUpClass* is called before tests in an individual class run. 
      and *tearDownClass* is called after tests in an individual class 
      have run. Both are called with the class as the only argument and 
      must be decorated as a *classmethod()*.

      .. code-block:: python

         import unittest
   
         class Test(unittest.TestCase):
            @classmethod
            def setUpClass(cls):
               cls._connection = createExpensiveConnectionObject()

            @classmethod
            def tearDownClass(cls):
             cls._connection.destroy()

   .. function:: run(result=None)

      Run the test, collecting the result into the test result object passed as *result*. If *result* is omitted 
      or *None*, a temporary result object is created (by calling the *defaultTestResult()* method) and used. 
      The result object is not returned to run()’s caller.

      The same effect may be had by simply calling the TestCase instance.

   .. function:: skipTest(reason)

      Calling this during a test method or *setUp()* skips the current test. 
      See Skipping tests and expected failures for more information.


   .. function:: debug()

      Run the test without collecting the result. This allows exceptions raised 
      by the test to be propagated to the caller, and can be used to support running 
      tests under a debugger.


The TestCase class provides several assert methods to check for and report failures. 
The following table lists the most commonly used methods (see the tables below for more 
assert methods):

   +-------------------------------------------+-----------------------------------------+
   | Method                                    | Checks that                             |
   +===========================================+=========================================+
   | assertEqual(a, b)                         | a == b                                  |
   +-------------------------------------------+-----------------------------------------+
   | assertNotEqual(a, b)                      | a != b                                  |
   +-------------------------------------------+-----------------------------------------+
   | assertTrue(x)                             | bool(x) is True                         |
   +-------------------------------------------+-----------------------------------------+
   | assertFalse(x)                            | bool(x) is False                        |
   +-------------------------------------------+-----------------------------------------+
   | assertIs(a, b)                            | a is b                                  |
   +-------------------------------------------+-----------------------------------------+
   | assertIsNot(a, b)                         | a is not b                              |
   +-------------------------------------------+-----------------------------------------+
   | assertIsNone(x)                           | x is None                               |
   +-------------------------------------------+-----------------------------------------+
   | assertIsNotNone(x)                        | x is not None                           |
   +-------------------------------------------+-----------------------------------------+
   | assertIn(a, b)                            | a in b                                  |
   +-------------------------------------------+-----------------------------------------+
   | assertNotIn(a, b)                         | a not in b                              |
   +-------------------------------------------+-----------------------------------------+
   | assertIsInstance(a, b)                    | isinstance(a, b)                        |
   +-------------------------------------------+-----------------------------------------+
   | assertNotIsInstance(a, b)                 | not isinstance(a, b)                    |
   +-------------------------------------------+-----------------------------------------+
   | ``assertRaises(exc, fun, *args, **kwds)`` | ``fun(*args, **kwds``) raises exc       |
   +-------------------------------------------+-----------------------------------------+
   | ``assertRaisesRegexp(exc, r, fun, *args,  | ``fun(*args, **kwds)`` raises exc       |
   | **kwds)``                                 | and the message matches regex r         |
   +-------------------------------------------+-----------------------------------------+
   | assertAlmostEqual(a, b)                   | round(a-b, 7) == 0                      |
   +-------------------------------------------+-----------------------------------------+
   | assertNotAlmostEqual(a, b)                | round(a-b, 7) != 0                      |
   +-------------------------------------------+-----------------------------------------+
   | assertGreater(a, b)                       | a > b                                   |
   +-------------------------------------------+-----------------------------------------+
   | assertGreaterEqual(a, b)                  | a >= b                                  |
   +-------------------------------------------+-----------------------------------------+
   | assertLess(a, b)                          | a < b                                   |
   +-------------------------------------------+-----------------------------------------+
   | assertLessEqual(a, b)                     | a <= b                                  |
   +-------------------------------------------+-----------------------------------------+
   | assertRegexpMatches(s, r)                 | r.search(s)                             |
   +-------------------------------------------+-----------------------------------------+
   | assertNotRegexpMatches(s, r)              | not r.search(s)                         |
   +-------------------------------------------+-----------------------------------------+
   | assertItemsEqual(a, b)                    | sorted(a) == sorted(b) and works        |
   |                                           | with unhashable objs                    |
   +-------------------------------------------+-----------------------------------------+
   | assertDictContainsSubset(a, b)            | all the key/value pairs in a exist in b |
   +-------------------------------------------+-----------------------------------------+

.. code-block:: python
   :caption: How to use

   with self.assertRaises(SomeException):
      do_something()

   with self.assertRaises(SomeException) as cm:
      do_something()

   the_exception = cm.exception
   self.assertEqual(the_exception.error_code, 3)

   self.assertRaisesRegexp(ValueError, "invalid literal for.*XYZ'$", int, 'XYZ')

   with self.assertRaisesRegexp(ValueError, 'literal'):
      int('XYZ')


Grouping tests
==============

.. class:: class unittest.TestSuite(tests=())

   This class represents an aggregation of individual test cases and test suites. 
   The class presents the interface needed by the test runner to allow it to be 
   run as any other test case. Running a *TestSuite* instance is the same as 
   iterating over the suite, running each test individually.

   If *tests* is given, it must be an iterable of individual test cases or other 
   test suites that will be used to build the suite initially. Additional methods 
   are provided to add test cases and suites to the collection later on.

*TestSuite* objects behave much like *TestCase* objects, except they do not actually 
implement a test. Instead, they are used to aggregate tests into groups of tests that 
should be run together. Some additional methods are available to add tests to TestSuite 
instances:

   .. function::  addTest(test)

      Add a TestCase or TestSuite to the suite.

   .. function:: addTests(tests)

      Add all the tests from an iterable of TestCase 
      and TestSuite instances to this test suite.

      This is equivalent to iterating over tests, 
      calling *addTest()* for each element.

   .. function:: countTestCases()

      Return the number of tests represented by this test object, 
      including all individual tests and sub-suites.

.. note:: 

   TestSuite shares the following methods with TestCase:

      * run(result)
      * debug()

   In the typical usage of a TestSuite object, the *run()* method 
   is invoked by a *TestRunner* rather than by the end-user test 
   harness.


Loading and running tests
=========================

.. class:: class unittest.TestLoader

   The TestLoader class is used to create test suites from classes and modules. 
   Normally, there is no need to create an instance of this class; the unittest 
   module provides an instance that can be shared as *unittest.defaultTestLoader*. 
   Using a subclass or instance, however, allows customization of some configurable 
   properties.

TestLoader objects have the following methods:

   .. function:: loadTestsFromTestCase(testCaseClass)

      Return a suite of all test cases contained 
      in the TestCase-derived testCaseClass.

   .. function:: loadTestsFromModule(module)

      Return a suite of all test cases contained in the given module. 
      This method searches module for classes derived from TestCase 
      and creates an instance of the class for each test method 
      defined for the class.

      .. note::

         Note While using a hierarchy of TestCase-derived classes can be convenient 
         in sharing fixtures and helper functions, defining test methods on base classes 
         that are not intended to be instantiated directly does not play well with this 
         method. Doing so, however, can be useful when the fixtures are different and 
         defined in subclasses.
         
         If a module provides a *load_tests* function it will be called to load the tests. 
         This allows modules to customize test loading. This is the **load_tests protocol**.


   .. function:: loadTestsFromName(name, module=None)

      Return a suite of all test cases given a string specifier.

      The specifier name is a “dotted name” that may resolve either 
      to a module, a test case class, a test method within a test 
      case class, a TestSuite instance, or a callable object which 
      returns a TestCase or TestSuite instance. These checks are 
      applied in the order listed here; that is, a method on a 
      possible test case class will be picked up as “a test method 
      within a test case class”, rather than “a callable object”.

      For example, if you have a module *SampleTests* containing a 
      TestCase-derived class *SampleTestCase* with three test methods 
      (*test_one(), test_two(), and test_three()*), the specifier 
      'SampleTests.SampleTestCase' would cause this method to 
      return a suite which will run all three test methods. 
      Using the specifier *SampleTests.SampleTestCase.test_two* 
      would cause it to return a test suite which will run only 
      the *test_two()* test method. The specifier can refer to 
      modules and packages which have not been imported; 
      they will be imported as a side-effect.

      The method optionally resolves name relative to the given module.

   .. function:: loadTestsFromNames(names, module=None)

      Similar to *loadTestsFromName()*, but takes a sequence of names 
      rather than a single name. The return value is a test suite 
      which supports all the tests defined for each name.

   .. function:: getTestCaseNames(testCaseClass)

      Return a sorted sequence of method names found 
      within testCaseClass; this should be a subclass of TestCase.


.. class :: class unittest.TestResult

   This class is used to compile information about which 
   tests have succeeded and which have failed.

   A TestResult object stores the results of a set of tests. 
   The TestCase and TestSuite classes ensure that results 
   are properly recorded; test authors do not need to worry 
   about recording the outcome of tests.

   Testing frameworks built on top of unittest may want access to t
   he TestResult object generated by running a set of tests for 
   reporting purposes; a TestResult instance is returned by the 
   *TestRunner.run()* method for this purpose.

.. class:: unittest.defaultTestLoader

   Instance of the TestLoader class intended to be shared. 
   If no customization of the TestLoader is needed, this 
   instance can be used instead of repeatedly creating new instances.

.. class:: unittest.TextTestRunner(stream=sys.stderr, descriptions=True, verbosity=1, failfast=False, buffer=False, resultclass=None)

   A basic test runner implementation which prints results on standard error. 
   It has a few configurable parameters, but is essentially very simple.
    Graphical applications which run test suites should provide alternate 
    implementations.

.. function:: unittest.main([module[, defaultTest[, argv[, testRunner[, testLoader[, exit[, verbosity[, failfast[, catchbreak[, buffer]]]]]]]]]])

   A command-line program that loads a set of tests from module and runs them; 
   this is primarily for making test modules conveniently executable. The simplest
   use for this function is to include the following line 
   at the end of a test script::

      if __name__ == '__main__':
         unittest.main()

   You can run tests with more detailed information by passing 
   in the verbosity argument::
      
      if __name__ == '__main__':
         unittest.main(verbosity=2)

   The *defaultTest* argument is the name of the test to run 
   if no test names are specified via *argv*. If not specified 
   or *None* and no test names are provided via *argv*, all 
   tests found in module are run.

   The *argv* argument can be a list of options passed to the program, 
   with the first element being the program name. If not specified or *None*, 
   the values of *sys.argv* are used.

   The *testRunner* argument can either be a test runner class or an already 
   created instance of it. By default *main* calls *sys.exit()* with an exit 
   code indicating success or failure of the tests run.

   The testLoader argument has to be a TestLoader instance, and defaults 
   to *defaultTestLoader*.

   *main* supports being used from the interactive interpreter by passing 
   in the argument *exit=False*. This displays the result on standard 
   output without calling *sys.exit()*:

      >>> from unittest import main
      >>> main(module='test_module', exit=False)

   The *failfast*, *catchbreak* and *buffer* parameters have the same effect 
   as the same-name command-line options.

   Calling *main* actually returns an instance of the TestProgram class. 
   This stores the result of the tests run as the result attribute.

