cmake_minimum_required(VERSION 3.0.0)
project(Sandbox VERSION 0.1.0)

link_libraries(hazel)
include_directories("${CMAKE_SOURCE_DIR}/include" "${CMAKE_SOURCE_DIR}/vendor/spdlog/include")

include(CTest)
enable_testing()


add_executable(${PROJECT_NAME} SandboxApp.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
