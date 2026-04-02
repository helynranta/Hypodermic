cmake_minimum_required(VERSION 3.15)

project(Hypodermic.Tests)

find_package(Boost REQUIRED COMPONENTS system unit_test_framework)

set(HypodermicTests_sources

    main.cpp

    CircularDependencyTests.cpp
    ClearAlignedInstanceCacheTests.cpp
    ContainerBuilderTests.cpp
    ContainerTests.cpp
    DefaultConstructibleTests.cpp
    FactoryTests.cpp
    IsCompleteTests.cpp
    MemoryTests.cpp
    NamedTests.cpp
    NestedContainerTests.cpp
    PersistentInstanceRegistrationTests.cpp
    ProvidedDependenciesTests.cpp
    ProvidedInstanceFactoryRegistrationTests.cpp
    ProvidedInstanceRegistrationTests.cpp
    RegistrationTests.cpp
    RuntimeRegistrationTests.cpp
    UseIfNoneTests.cpp
)

include_directories("..")

add_executable(${PROJECT_NAME} ${HypodermicTests_sources})
target_compile_definitions(${PROJECT_NAME} PRIVATE -DBOOST_TEST_DYN_LINK)
target_link_libraries(${PROJECT_NAME} Boost::boost Boost::unit_test_framework)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)
add_test(cmake_${PROJECT_NAME} ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} --result_code=no --report_level=no)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME})
