project(Hypodermic.Tests)

find_package(Boost REQUIRED COMPONENTS system unit_test_framework)

include_directories("${CMAKE_SOURCE_DIR}")

add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PUBLIC
        main.cpp

        CircularDependencyTests.cpp
        ContainerBuilderTests.cpp
        ContainerTests.cpp
        DefaultConstructibleTests.cpp
        FactoryTests.cpp
        IsCompleteTests.cpp
        MemoryTests.cpp
        NamedTests.cpp
        NestedContainerTests.cpp
        PerformanceTests.cpp
        PersistentInstanceRegistrationTests.cpp
        ProvidedDependenciesTests.cpp
        ProvidedInstanceFactoryRegistrationTests.cpp
        ProvidedInstanceRegistrationTests.cpp
        RegistrationTests.cpp
        RuntimeRegistrationTests.cpp
        UseIfNoneTests.cpp)

target_link_libraries(${PROJECT_NAME} Boost::boost Boost::unit_test_framework)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)

add_test(cmake_Hypodermic.Tests ${CMAKE_CURRENT_BINARY_DIR}/Hypodermic.Tests --result_code=no --report_level=no)