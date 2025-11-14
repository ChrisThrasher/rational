cmake_minimum_required(VERSION 3.28)
project(rational
    VERSION 1.0.0
    LANGUAGES CXX
    DESCRIPTION "C++20 rational number class template"
)

add_library(rational INTERFACE)
add_library(rational::rational ALIAS rational)
target_sources(rational INTERFACE FILE_SET HEADERS
    BASE_DIRS include
    FILES include/rational/rational.hpp
)
target_compile_features(rational INTERFACE cxx_std_20)

include(GNUInstallDirs)
install(TARGETS rational EXPORT rational-targets FILE_SET HEADERS)
install(
    EXPORT rational-targets
    NAMESPACE rational::
    DESTINATION ${CMAKE_INSTALL_DATADIR}/rational
)

include(CTest)
if(BUILD_TESTING)
    add_subdirectory(tests)
endif()

if(NOT PROJECT_IS_TOP_LEVEL)
    return()
endif()

add_custom_target(format
    COMMAND clang-format -i `git ls-files *.hpp *.cpp`
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    USES_TERMINAL
)
add_custom_target(tidy
    COMMAND run-clang-tidy -p ${CMAKE_BINARY_DIR} `git ls-files *.cpp`
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    USES_TERMINAL
)
