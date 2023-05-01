include(CTest)
enable_testing()

set(HEADERS "${HAZEL_SOURCE_DIR}/include/Hazel/hazel.h" 
            "Application.h"
            "EntryPoint.h")
set(SOURCES "Application.cpp")

add_library(hazel SHARED ${HEADERS} ${SOURCES})


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)