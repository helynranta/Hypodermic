cmake_minimum_required(VERSION 3.25)

option(HYPODERMIC_ENABLE_TESTS "build unit tests" OFF)
if (HYPODERMIC_ENABLE_TESTS)
    list(APPEND VCPKG_MANIFEST_FEATURES "tests")
endif()

project(Hypodermic)

set(HYPODERMIC_VERSION_MAJOR "2")
set(HYPODERMIC_VERSION_MINOR "5")
set(HYPODERMIC_VERSION_PATCH "0")
set(HYPODERMIC_VERSION
    "${HYPODERMIC_VERSION_MAJOR}.${HYPODERMIC_VERSION_MINOR}.${HYPODERMIC_VERSION_PATCH}"
)

add_subdirectory(Hypodermic)

if(HYPODERMIC_ENABLE_TESTS)
    enable_testing()
    add_subdirectory(Hypodermic.Tests)
endif()

# uninstall target
##################
#

configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY
)

add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake
)


# Packaging stuff
#################
#

set(CPACK_PACKAGE_VERSION_MAJOR "${HYPODERMIC_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${HYPODERMIC_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${HYPODERMIC_VERSION_PATCH}")

set(CPACK_SOURCE_PACKAGE_FILE_NAME
    "${CMAKE_PROJECT_NAME}-${HYPODERMIC_VERSION}"
)

set(CPACK_SOURCE_GENERATOR "TBZ2")
set(CPACK_SOURCE_IGNORE_FILES
    "/.hg/"
    "/.hgignore$"
    "build/"
    "ipch/"
    "/resources/"
    ".sdf$;.suo$;.tss$"
)

include(CPack)
add_custom_target(dist COMMAND ${CMAKE_MAKE_PROGRAM} package_source)
