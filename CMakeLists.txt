cmake_minimum_required(VERSION 3.0.0)
project(HAZEL VERSION 0.1.0)

include(CTest)
enable_testing()

add_subdirectory(vendor/GLFW)
add_subdirectory(vendor/glad)
add_subdirectory(vendor/Imgui)

add_subdirectory(src)
add_subdirectory(Sandbox)



set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

