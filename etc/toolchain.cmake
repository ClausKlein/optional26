include_guard(GLOBAL)

if(UNIX)
    include("${CMAKE_CURRENT_LIST_DIR}/gcc-flags.cmake")

    set(CMAKE_C_COMPILER gcc)
    set(CMAKE_CXX_COMPILER g++)
    set(GCOV_EXECUTABLE "gcov" CACHE PATH "GCOV executable")
else()
    # TODO(CK): include("${CMAKE_CURRENT_LIST_DIR}/cl-flags.cmake")

    set(CMAKE_C_COMPILER cl)
    set(CMAKE_CXX_COMPILER cl)
    set(GCOV_EXECUTABLE "" CACHE PATH "GCOV executable")
endif()
