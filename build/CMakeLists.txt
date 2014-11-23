#Require
cmake_minimum_required(VERSION 2.8)

#Projet Name
project( lm )

#compiler
if (UNIX)
   if (APPLE)
      set (CMAKE_CXX_COMPILER g++)
   else (APPLE)
      set (CMAKE_CXX_COMPILER g++)
   endif (APPLE)
endif (UNIX)

#flag
#if (UNIX)
#   if (APPLE)
#       set (CMAKE_CXX_FLAGS)
#   else (APPLE)
       set (CMAKE_CXX_FLAGS "-std=c++11 -g3")
#   endif (APPLE)
#endif (UNIX)

SET(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "-L/lib/")

# Add FindTBB directory to CMake's module path
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
    "${CMAKE_CURRENT_SOURCE_DIR}/.")

#Check Package
find_package( OpenCV REQUIRED )

#Compiling file and binary generation
 #Get all sources files
 file(
   GLOB_RECURSE
   V_SOURCE
   ../src/*.[ch][ch]
   )

 #Add Files
 add_executable(
   lm
   ${V_SOURCE}
 )
#Link target
target_link_libraries( lm ${OpenCV_LIBS} )

#Custom Cmd Clean
ADD_CUSTOM_TARGET (distclean @echo cleaning for source distribution)
  SET(DISTCLEANED
   cmake.depends
   cmake.check_depends
   CMakeCache.txt
   cmake.check_cache
   *.cmake
   Makefile
   core core.*
   bin
   PrPa_Projet
   CMakeFiles
   *~
   *.swp
  )

  ADD_CUSTOM_COMMAND(
    DEPENDS clean
    COMMENT "distribution clean"
    COMMAND rm
    ARGS    -Rf CMakeTmp ${DISTCLEANED}
    TARGET  distclean
  )
