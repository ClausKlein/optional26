# CMakeLists.txt                                                    -*-CMake-*-
#
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

cmake_minimum_required(VERSION 3.27...3.31)

# set a default CXX standard for the tools and targets that do not specify them.
# If commented, the latest supported standard for your compiler is automatically set.
# set(CMAKE_CXX_STANDARD 20)

project(beman_optional26 VERSION 0.0.0 LANGUAGES CXX)

# Includes
include(CPACK)
include(FetchContent)

set(TARGET_PACKAGE_NAME ${PROJECT_NAME})
set(TARGETS_EXPORT_NAME ${TARGET_PACKAGE_NAME}-targets)
set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/${TARGET_PACKAGE_NAME})

option(
    OPTIONAL26_ENABLE_TESTING
    "Enable building tests and test infrastructure"
    ${PROJECT_IS_TOP_LEVEL}
)

# Build the tests if enabled via the option OPTIONAL26_ENABLE_TESTING
if(OPTIONAL26_ENABLE_TESTING)
    enable_testing()

    # Fetch GoogleTest
    FetchContent_Declare(
        googletest
        EXCLUDE_FROM_ALL
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG
            e39786088138f2749d64e9e90e0f9902daa77c40 # release-1.15.0
    )
    FetchContent_MakeAvailable(googletest)
endif()

set(CMAKE_VERIFY_INTERFACE_HEADER_SETS ON)

# Create the library target and named header set for beman_optional26
add_library(beman_optional26 INTERFACE)
add_library(Beman::Optional26::beman_optional26 ALIAS beman_optional26)
target_sources(
    beman_optional26
    PUBLIC FILE_SET beman_optional26_headers TYPE HEADERS BASE_DIRS include
)
target_compile_features(
    beman_optional26
    INTERFACE
        "$<$<COMPILE_FEATURES:cxx_std_26>:cxx_std_26>"
        "$<$<NOT:$<COMPILE_FEATURES:cxx_std_26>>:cxx_std_23>"
)

if(OPTIONAL26_ENABLE_TESTING)
    # Create the library target and named header set for testing beman_optional26
    # and mark the set private
    add_executable(beman_optional26_test)
    target_sources(
        beman_optional26_test
        PRIVATE
            FILE_SET beman_optional26_test_headers
            TYPE HEADERS
            BASE_DIRS src
    )

    add_subdirectory(src/beman/optional26/tests)
endif()

add_subdirectory(include/beman/optional26)

add_subdirectory(examples)

include(CMakePackageConfigHelpers)

# install
write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/${TARGET_PACKAGE_NAME}-config-version.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(
    cmake/Config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/${TARGET_PACKAGE_NAME}-config.cmake
    INSTALL_DESTINATION ${INSTALL_CONFIGDIR}
)

install(
    FILES
        ${CMAKE_CURRENT_BINARY_DIR}/${TARGET_PACKAGE_NAME}-config.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/${TARGET_PACKAGE_NAME}-config-version.cmake
    DESTINATION ${INSTALL_CONFIGDIR}
)

# # This will be used to replace @PACKAGE_cmakeModulesDir@
# set(cmakeModulesDir cmake)
# configure_package_config_file(
#     cmake/Config.cmake.in
#     beman_optional26-config.cmake
#     INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/beman_optional26/
#     PATH_VARS cmakeModulesDir
#     NO_SET_AND_CHECK_MACRO
#     NO_CHECK_REQUIRED_COMPONENTS_MACRO
# )
#
# install(
#     FILES ${CMAKE_CURRENT_BINARY_DIR}/beman_optional26-config.cmake
#     DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/beman_optional26/
#     COMPONENT beman_optional26_development
# )

# Coverage
configure_file("cmake/gcovr.cfg.in" gcovr.cfg @ONLY)

add_custom_target(
    process_coverage
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Running gcovr to process coverage results"
    COMMAND mkdir -p coverage
    COMMAND gcovr --config gcovr.cfg .
)
