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

.. code-block:: sh
   :caption: tip_radar project structure

   $ ls -R trip_radar/
   trip_radar/:
   CMakeList.txt  trip_diary  trip_recorder
   
   trip_radar/trip_diary:
   CMakeList.txt
   
   trip_radar/trip_recorder:
   CMakeList.txt

.. code-block:: none
   :caption: CMakeList.txt for trip_radar

   CMAKE_MINIMUM_REQUIRED (VERSION 2.6)

   ADD_SUBDIRECTORY("trip_recorder" "tmp/trip_recorder") # assign intermediate directory for build
   ADD_SUBDIRECTORY("trip_diary" "tmp/trip_diary")


.. code-block:: none
   :caption: CMakeList.txt for trip_recorder

   cmake_minimum_required (VERSION 2.6)

   set (PROC_OUTPUT "trip_recorder")
   project (${PROC_OUTPUT})
   
   set (BASE_PATH ${CMAKE_CURRENT_SOURCE_DIR})
   set (EXECUTABLE_OUTPUT_PATH "${BASE_PATH}/bin") # assign binary output directory
   set (CMAKE_BUILD_TYPE "Release")
   
   IF (${CMAKE_GENERATOR} STREQUAL "Visual Studio 12 Win64")
      SET (CMAKE_CXX_FLAGS_DEBUG "/MT")
      SET (CMAKE_CXX_FLAGS_RELEASE "/MT")
   
      add_definitions(
         -DAMD64
         -DALLOW_OUTPUT_LOG
      )
   
   ELSEIF (${CMAKE_GENERATOR} STREQUAL "Unix Makefiles")
   
      add_definitions(
         -DAMD64
         -DALLOW_OUTPUT_LOG
      )
   
      SET (CMAKE_C_FLAGS_DEBUG "-Wall -g -fshort-wchar -fwide-exec-charset=UTF-16LE -m64")
      SET (CMAKE_C_FLAGS_RELEASE "-Wall -O2 -fshort-wchar -fwide-exec-charset=UTF-16LE -m64")
      SET (CMAKE_CXX_FLAGS_DEBUG "-std=c++11 -Wall -g -fshort-wchar -fwide-exec-charset=UTF-16LE -m64")
      SET (CMAKE_CXX_FLAGS_RELEASE "-std=c++11 -Wall -O2 -fshort-wchar -fwide-exec-charset=UTF-16LE -m64")
   
   ENDIF ()

   include_directories(path/to/common_include)
   link_directories(path/to/common_library)
      
   IF (${CMAKE_BUILD_TYPE} STREQUAL "Debug")

      SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS_DEBUG}")
      SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_DEBUG}")
      include_directories( ${BASE_PATH}/../../third-party-lib/Debug/include )
      link_directories(${BASE_PATH}/../../third-party-lib/Debug/lib)

   ELSE()

      SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS_RELEASE}")
      SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_RELEASE}")
      include_directories( ${BASE_PATH}/../../third-party-lib/Debug/include )
      link_directories(${BASE_PATH}/../../third-party-lib/Release/lib)

   ENDIF ()
   
   file(GLOB_RECURSE SRC "src/*.cpp" "src/*.c")
   add_executable(${PROC_OUTPUT} ${SRC})
   
   IF (${CMAKE_GENERATOR} STREQUAL "Unix Makefiles")
      SET (THIRD_PARTY_LIB "-Wl,--start-group" 
         curl
         sqlite3
         "-Wl,--end-group"
         )
   
      SET (SYS_LIB m rt dl pthread)
   
      target_link_libraries(${PROC_OUTPUT} ${THIRD_PARTY_LIB} ${SYS_LIB})
   ENDIF ()
   

.. rubric:: Footnotes

.. [#] `CMake FAQ <https://gitlab.kitware.com/cmake/community/wikis/FAQ>`_