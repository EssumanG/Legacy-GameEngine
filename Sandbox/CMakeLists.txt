cmake_minimum_required(VERSION 3.0.0)
project(Sandbox VERSION 0.1.0)

link_libraries(legacy)
include_directories("${CMAKE_SOURCE_DIR}/include" "${CMAKE_SOURCE_DIR}/vendor/spdlog/include"
                    "${CMAKE_SOURCE_DIR}/vendor/Imgui" "${CMAKE_SOURCE_DIR}/src/")

include(CTest)
enable_testing()

set(Sandbox2D_files "Sandbox2D.h" "Sandbox2D.cpp")
add_executable(${PROJECT_NAME} SandboxApp.cpp ${Sandbox2D_files})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
