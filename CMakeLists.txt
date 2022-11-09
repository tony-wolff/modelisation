# Created by the script cgal_create_CMakeLists
# This is the CMake script for compiling a set of CGAL applications.

cmake_minimum_required(VERSION 3.1...3.15)

project( modelisation )


# CGAL and its components
find_package( CGAL QUIET COMPONENTS  )
find_package(CGAL REQUIRED OPTIONAL_COMPONENTS Qt5)
add_definitions(-DCGAL_USE_BASIC_VIEWER)
if ( NOT CGAL_FOUND )

  message(STATUS "This project requires the CGAL library, and will not be compiled.")
  return()  

endif()

# Boost and its components
find_package( Boost REQUIRED )

if ( NOT Boost_FOUND )

  message(STATUS "This project requires the Boost library, and will not be compiled.")

  return()  

endif()

# include for local directory

# include for local package


# Creating entries for all C++ files with "main" routine
# ##########################################################


create_single_source_cgal_program( "point_set_read_xyz.cpp" )
create_single_source_cgal_program("draw_point_set.cpp")

