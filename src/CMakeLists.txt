include(CTest)
enable_testing()
include_directories("${CMAKE_SOURCE_DIR}/vendor/spdlog/include")

set(HEADERS "${HAZEL_SOURCE_DIR}/include/Hazel/hazel.h" 
            "Application.h"
            "EntryPoint.h"
            "log.h")
set(SOURCES "Application.cpp"
            "log.cpp")

add_library(hazel SHARED ${HEADERS} ${SOURCES})


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)