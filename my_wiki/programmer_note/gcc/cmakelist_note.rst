***************
CMakeList Howto
***************

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
   project (trip_recorder)
   
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
   
      #specify CMAKE_BUILD_TYPE to Debug or Release
      SET (CMAKE_C_FLAGS_DEBUG "-Wall -g -fshort-wchar -fwide-exec-charset=UTF-16LE -m64")
      SET (CMAKE_C_FLAGS_RELEASE "-Wall -O2 -fshort-wchar -fwide-exec-charset=UTF-16LE -m64")
   
      SET (CMAKE_CXX_FLAGS_DEBUG "-std=c++11 -Wall -g -fshort-wchar -fwide-exec-charset=UTF-16LE -m64")
      SET (CMAKE_CXX_FLAGS_RELEASE "-std=c++11 -Wall -O2 -fshort-wchar -fwide-exec-charset=UTF-16LE -m64")
   
      #if CMAKE_BUILD_TYPE is None, using these flags
      SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS_RELEASE}")
      SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_RELEASE}")
   
   ENDIF ()
   
   IF (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
      include_directories(
         ${BASE_PATH}/../../third-party-lib/Debug/include
      )
      
      link_directories(
         ${BASE_PATH}/../../third-party-lib/Debug/lib
      )
   ELSE()
      include_directories(
         ${BASE_PATH}/../../third-party-lib/Release/include
      )
      
      link_directories(
         ${BASE_PATH}/../../third-party-lib/Release/lib
      )
   ENDIF ()
   
   file(GLOB_RECURSE SRC "src/*.cpp" "src/*.c")
   
   add_executable(trip_recorder ${SRC})
   
   IF (${CMAKE_GENERATOR} STREQUAL "Unix Makefiles")
      SET (THIRD_PARTY_LIB "-Wl,--start-group" 
         sqlite3
         curl
         "-Wl,--end-group"
         )
   
      SET (SYS_LIB pthread dl rt m)
   
      target_link_libraries(trip_recorder ${THIRD_PARTY_LIB} ${SYS_LIB})
   ENDIF ()
   