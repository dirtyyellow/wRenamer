cmake_minimum_required(VERSION 3.10) 
project(wRenamer) 


set(Exiv2_INCLUDE_DIRS "C:/Program Files (x86)/exiv2/include")
set(Exiv2_LIBRARY_DIRS "C:/Program Files (x86)/exiv2/lib")
find_library(Exiv2_LIBRARIES NAMES exiv2 PATHS ${Exiv2_LIBRARY_DIRS})


if(NOT Exiv2_LIBRARIES)
    message(FATAL_ERROR "failed")
endif()

aux_source_directory(src SRC_INC)
list(APPEND SRC_PAR main.cpp)
add_executable(wRenamer ${SRC_INC} ${SRC_PAR})
target_link_libraries(wRenamer ${Exiv2_LIBRARIES})
target_include_directories(wRenamer PUBLIC ${Exiv2_INCLUDE_DIRS})
include_directories(include) 