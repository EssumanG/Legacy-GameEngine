include(CTest)
enable_testing()
include_directories("${CMAKE_SOURCE_DIR}/vendor/spdlog/include" 
                    "${CMAKE_SOURCE_DIR}/src"
                    "${CMAKE_SOURCE_DIR}/vendor/GLFW/include"
                    "${CMAKe_SOURCE_DIR}/vendor/glad/include")


set(HEADERS "${HAZEL_SOURCE_DIR}/include/Hazel/hazel.h" 
            "Core.h"
            "Application.h"
            "EntryPoint.h"
            "log.h" 
            "Events/Event.h"
            "Events/KeyEvent.h"
            "Events/MouseEvent.h"
            "Events/ApplicationEvent.h"
            "Window.h"
            "Layer.h"
            "LayerStack.h")
set(SOURCES "Application.cpp"
            "log.cpp"
            "Layer.cpp"
            "LayerStack.cpp")

if (UNIX)
    list(APPEND HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/Platform/Unix/UnixWindow.h")
    list(APPEND SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/Platform/Unix/UnixWindow.cpp")
endif()




add_library(hazel SHARED ${HEADERS} ${SOURCES})

# Should be defined only on Debug mode
target_compile_definitions(hazel PUBLIC HZ_ENABLE_ASSERTS)
add_compile_definitions("GLFW_INCLUDE_NONE")
target_precompile_headers(hazel PUBLIC "hz_pch.h")

target_link_libraries(hazel glfw)
target_link_libraries(hazel Glad)



set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

message("DIR  ${CMAKE_SOURCE_DIR}/src")

message("all header files: ${HEADERS}")