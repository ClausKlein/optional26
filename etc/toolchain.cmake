include_guard(GLOBAL)

if(UNIX)
    include("${CMAKE_CURRENT_LIST_DIR}/clang-flags.cmake")

    set(CMAKE_C_COMPILER clang)
    set(CMAKE_CXX_COMPILER clang++)
else()
    # include("${CMAKE_CURRENT_LIST_DIR}/cl-flags.cmake")

    set(CMAKE_C_COMPILER cl)
    set(CMAKE_CXX_COMPILER cl)
endif()
