cmake_minimum_required(VERSION 3.20)

project(CPPTest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


# application
add_subdirectory(src)

# tests
enable_testing()
add_subdirectory(tests)

# 3rd parties / SOUP
add_subdirectory(3rdParties)


