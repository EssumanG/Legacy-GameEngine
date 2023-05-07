include(CTest)
enable_testing()
include_directories("${CMAKE_SOURCE_DIR}/vendor/spdlog/include" 
                    "${CMAKE_SOURCE_DIR}/vendor/GLFW/include"
                    "${CMAKE_SOURCE_DIR}/vendor/glad/include"
                    "${CMAKE_SOURCE_DIR}/vendor/Imgui"
                    "${CMAKE_CURRENT_SOURCE_DIR}")

set(IMGUI_HEADERS "Imgui/ImGuiLayer.h" "${CMAKE_CURRENT_SOURCE_DIR}/Platform/OpenGL/imgui_opengl_renderer.h")
set(IMGUI_SOURCES "Imgui/ImGuiLayer.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/Platform/OpenGL/imgui_opengl_renderer.cpp" "${CMAKE_SOURCE_DIR}/vendor/Imgui/backends/imgui_impl_glfw.cpp")

list(APPEND IMGUI_FILES ${IMGUI_HEADERS} ${IMGUI_SOURCES})
set(HEADERS "${HAZEL_SOURCE_DIR}/include/Legacy/legacy.h" 
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
            "LayerStack.h"
            "Input.h")
set(SOURCES "Application.cpp"
            "log.cpp"
            "Layer.cpp"
            "LayerStack.cpp")

if (UNIX)
    list(APPEND HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/Platform/Unix/UnixWindow.h"
                        "${CMAKE_CURRENT_SOURCE_DIR}/Platform/Unix/UnixInput.h")
    list(APPEND SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/Platform/Unix/UnixWindow.cpp"
                        "${CMAKE_CURRENT_SOURCE_DIR}/Platform/Unix/UnixInput.cpp")
endif()




add_library(legacy SHARED ${HEADERS} ${SOURCES} 
                         ${IMGUI_FILES})

# Should be defined only on Debug mode
target_compile_definitions(legacy PUBLIC LG_ENABLE_ASSERTS)
add_compile_definitions("GLFW_INCLUDE_NONE")
target_precompile_headers(legacy PUBLIC "lg_pch.h")

target_link_libraries(legacy glfw)
target_link_libraries(legacy Glad)
target_link_libraries(legacy imgui)



set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

message("DIR  ${CMAKE_SOURCE_DIR}/src")

message("all header files: ${HEADERS}")