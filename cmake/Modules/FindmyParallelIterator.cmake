# - Try to find ThreadPool
# Once done this will define
#  myParallelIterator_FOUND - System has myParallelIterator
#  myParallelIterator_INCLUDE_DIRS - The myParallelIterator include directories
#  myParallelIterator_LIBRARIES - The libraries needed to use myParallelIterator

find_path(myParallelIterator_INCLUDE_DIR
	NAMES myParallelIterator.hpp
	HINTS ${myParallelIterator_ROOT}/include
	DOC "The myParallelIterator include directory"
)
message(STATUS ${myParallelIterator_INCLUDE_DIR})

find_library(myParallelIterator_LIBRARY
	NAMES myParallelIterator
	HINTS ${myParallelIterator_ROOT}/lib
	DOC "The myParallelIterator library"
)

if(myParallelIterator_INCLUDE_DIR AND myParallelIterator_LIBRARY)
	set(myParallelIterator_FOUND 1)
endif()

# Handle the QUIETLY and REQUIRED arguments and set LOGGING_FOUND to TRUE if all listed variables are TRUE
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(myParallelIterator DEFAULT_MSG myParallelIterator_INCLUDE_DIR myParallelIterator_LIBRARY)

if(myParallelIterator_FOUND)
	set(myParallelIterator_LIBRARIES ${myParallelIterator_LIBRARY} )
	set(myParallelIterator_INCLUDE_DIRS ${myParallelIterator_INCLUDE_DIR} )
endif()

# Tell cmake ThreadPools to ignore the "local" variables
mark_as_advanced(myParallelIterator_INCLUDE_DIR myParallelIterator_LIBRARY)
