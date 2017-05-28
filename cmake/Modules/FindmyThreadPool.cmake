# - Try to find ThreadPool
# Once done this will define
#  myThreadPool_FOUND - System has myThreadPool
#  myThreadPool_INCLUDE_DIRS - The myThreadPool include directories
#  myThreadPool_LIBRARIES - The libraries needed to use myThreadPool

find_path(myThreadPool_INCLUDE_DIR
	NAMES myThreadPool.hpp
	HINTS ${myThreadPool_ROOT}/include
	DOC "The myThreadPool include directory"
)
message(STATUS ${myThreadPool_INCLUDE_DIR})

find_library(myThreadPool_LIBRARY
	NAMES myThreadPool
	HINTS ${myThreadPool_ROOT}/lib
	DOC "The myThreadPool library"
)

if(myThreadPool_INCLUDE_DIR AND myThreadPool_LIBRARY)
	set(myThreadPool_FOUND 1)
endif()

# Handle the QUIETLY and REQUIRED arguments and set LOGGING_FOUND to TRUE if all listed variables are TRUE
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(myThreadPool DEFAULT_MSG myThreadPool_INCLUDE_DIR myThreadPool_LIBRARY)

if(myThreadPool_FOUND)
	set(myThreadPool_LIBRARIES ${myThreadPool_LIBRARY} )
	set(myThreadPool_INCLUDE_DIRS ${myThreadPool_INCLUDE_DIR} )
endif()

# Tell cmake ThreadPools to ignore the "local" variables
mark_as_advanced(myThreadPool_INCLUDE_DIR myThreadPool_LIBRARY)
