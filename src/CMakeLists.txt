include(CTest)
enable_testing()
include_directories("${CMAKE_SOURCE_DIR}/vendor/spdlog/include" "${CMAKE_SOURCE_DIR}/src")


set(HEADERS "${HAZEL_SOURCE_DIR}/include/Hazel/hazel.h" 
            "Core.h"
            "Application.h"
            "EntryPoint.h"
            "log.h" 
            "Events/Event.h"
            "Events/KeyEvent.h"
            "Events/MouseEvent.h"
            "Events/ApplicationEvent.h")
set(SOURCES "Application.cpp"
            "log.cpp")

add_library(hazel SHARED ${HEADERS} ${SOURCES})

target_precompile_headers(hazel PUBLIC "hz_pch.h")


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

message("DIR  ${CMAKE_SOURCE_DIR}/src")