***************
CMakeList Howto
***************

#. Add include directories to the build.

   Syntax: ``include_directories([AFTER|BEFORE] [SYSTEM] dir1 [dir2 ...])``

   Add the given directories to those the compiler uses to search for include files.
   Relative paths are interpreted as relative to the current source directory.

   The include directories are added to the INCLUDE_DIRECTORIES directory property for the current *CMakeLists* file.
   They are also added to the INCLUDE_DIRECTORIES target property for each target in the current CMakeLists file.
   The target property values are the ones used by the generators.

   By default the directories specified are appended onto the current list of directories.
   This default behavior can be changed by setting ``CMAKE_INCLUDE_DIRECTORIES_BEFORE`` to ``ON``.
   By using ``AFTER`` or ``BEFORE`` explicitly, you can select between appending and prepending,
   independent of the default.

   If the SYSTEM option is given, the compiler will be told the directories are meant as
   system include directories on some platforms. Signalling this setting might achieve effects
   such as the compiler skipping warnings, or these fixed-install system files not being considered
   in dependency calculations.

#. Specify directories in which the linker will look for libraries.

   Syntax: ``link_directories(directory1 directory2 ...)``

   Specify the paths in which the linker should search for libraries.
   The command will apply only to targets created after it is called.
   Relative paths given to this command are interpreted as relative
   to the current source directory.

   **Note** that this command is rarely necessary. Library locations returned by ``find_package()``
   and ``find_library()`` are absolute paths. Pass these absolute library file paths directly to the
   ``target_link_libraries()`` command. CMake will ensure the linker finds them.

#. Link a target to given libraries.

   .. code-block:: sh

      target_link_libraries(<target> [item1 [item2 [...]]]
                      [[debug|optimized|general] <item>] ...)

   Specify libraries or flags to use when linking a given target.
   The named ``target`` must have been created in the current directory
   by a command such as ``add_executable()`` or ``add_library()``.
   The remaining arguments specify library names or flags. Repeated calls
   for the same ``target`` append items in the order called.

#. add_definitions

   Syntax: ``add_definitions(-DFOO -DBAR ...)``

   Adds ``-D`` define flags to the compilation of source files.

   Adds definitions to the compiler command line for sources in the current directory and below.
   This command can be used to add any flags, but it is intended to add preprocessor definitions.

#. Include source files

   Syntax::

      file(GLOB variable [RELATIVE path] [globbing expressions]...)
      file(GLOB_RECURSE variable [RELATIVE path]
        [FOLLOW_SYMLINKS] [globbing expressions]...)

   ``GLOB`` will generate a list of all files that match the globbing expressions
   and store it into the variable. ``GLOB_RECURSE`` will generate a list similar to
   the regular ``GLOB``, except it will traverse all the subdirectories of the matched directory and match the files.

#. Hot enviroments

    .. code-block:: sh

        CMAKE_CURRENT_BINARY_DIR
        The path to the binary directory currently being processed.

        CMAKE_CURRENT_SOURCE_DIR
        The path to the source directory currently being processed.

        CMAKE_BUILD_TYPE
        project configuration, such as Debug, Release

        CMAKE_SYSTEM_NAME
        the name of os for which CMake to build.

        CMAKE_INSTALL_PREFIX
        If ``make install`` is invoked or INSTALL is built, this directory is prepended onto all install directories.
        This variable defaults to ``/usr/local`` on UNIX and ``c:/Program Files/${PROJECT_NAME}`` on Windows.

    Refer to CMake variables [#CMake_Environments]_ for further information.

#. CMAKE to pass customized Environments

    .. code-block:: sh

        # -D <var>:<type>=<value>, -D <var>=<value>
        # for example to pass the build type for the generator,
        # you can run
        cmake -DCMAKE_BUILD_TYPE=Debug ..

#. target_compile_features specified unknown feature "cxx_std_17" for target

    c++17 is supported after cmake v3.8, so upgrade cmake.

#. make to pass macro preprocessors

    Solution: ``make CXXFLAGS=-DDEBUG backtrace_sudoku_solver``.

.. rubric:: Footnotes

.. [#] `CMake FAQ <https://gitlab.kitware.com/cmake/community/wikis/FAQ>`_
.. [#] `CMake_Environments <https://cmake.org/cmake/help/v3.0/manual/cmake-variables.7.html?highlight=cmake_current_list_dir>`_
