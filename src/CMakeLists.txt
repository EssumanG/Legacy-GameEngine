include(CTest)
enable_testing()
include_directories("${CMAKE_SOURCE_DIR}/vendor/spdlog/include" 
                    "${CMAKE_SOURCE_DIR}/vendor/GLFW/include"
                    "${CMAKE_SOURCE_DIR}/vendor/glad/include"
                    "${CMAKE_SOURCE_DIR}/vendor/Imgui"
                    "${CMAKE_SOURCE_DIR}/vendor/stb_image"
                    "${CMAKE_CURRENT_SOURCE_DIR}"
                    "${CMAKE_SOURCE_DIR}")

set(IMGUI_HEADERS "Imgui/ImGuiLayer.h" "${CMAKE_SOURCE_DIR}/vendor/Imgui/backends/imgui_impl_opengl3.h"
                  "${CMAKE_SOURCE_DIR}/vendor/Imgui/backends/imgui_impl_glfw.h")
set(IMGUI_SOURCES "Imgui/ImGuiLayer.cpp" "Imgui/ImGuiBuild.cpp"  )
set(STB_IMG_FILES "${CMAKE_SOURCE_DIR}/vendor/stb_image/stb_image.cpp")

list(APPEND IMGUI_FILES ${IMGUI_HEADERS} ${IMGUI_SOURCES})
set(HEADERS "${HAZEL_SOURCE_DIR}/include/Legacy/legacy.h" 
            "Debug/Instrumentor.h"
            "Core/Core.h"
            "Core/Application.h"
            "Core/EntryPoint.h"
            "Core/log.h"
            "Events/Event.h"
            "Events/KeyEvent.h"
            "Events/MouseEvent.h"
            "Events/ApplicationEvent.h"
            "Core/Window.h"
            "Core/Layer.h"
            "Core/LayerStack.h"
            "Renderer/GraphicsContext.h"
            "Renderer/Shader.h"
            "Core/Input.h"
            "Renderer/Buffer.h"
            "Renderer/Renderer.h"
            "Renderer/Renderer2D.h"
            "Renderer/RendererAPI.h"
            "Renderer/OrthographicCamera.h"
            "Renderer/RenderCommand.h"
            "Renderer/VertexArray.h"
            "Renderer/Texture.h"
            "Core/Timestep.h"
            "Renderer/OrthographicCameraController.h")
set(SOURCES "Core/Application.cpp"
            "Core/log.cpp"
            "Core/Layer.cpp"
            "Core/LayerStack.cpp"
            "Renderer/Buffer.cpp"
            "Renderer/Shader.cpp"
            "Renderer/Renderer.cpp"
            "Renderer/Renderer2D.cpp"
            "Renderer/RendererAPI.cpp"
            "Renderer/OrthographicCamera.cpp"
            "Renderer/RenderCommand.cpp"
            "Renderer/VertexArray.cpp"
            "Renderer/Texture.cpp"
            "Renderer/OrthographicCameraController.cpp"
            )

if (UNIX)
    list(APPEND HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/Platform/Unix/UnixWindow.h"
                        "${CMAKE_CURRENT_SOURCE_DIR}/Platform/Unix/UnixInput.h")
    list(APPEND SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/Platform/Unix/UnixWindow.cpp"
                        "${CMAKE_CURRENT_SOURCE_DIR}/Platform/Unix/UnixInput.cpp")
endif()

set(OPENGL  "${CMAKE_CURRENT_SOURCE_DIR}/Platform/OpenGL/OpenGLContext.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/Platform/OpenGL/OpenGLContext.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/Platform/OpenGL/OpenGLBuffer.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/Platform/OpenGL/OpenGLBuffer.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/Platform/OpenGL/OpenGLVertexArray.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/Platform/OpenGL/OpenGLVertexArray.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/Platform/OpenGL/OpenGLRendererAPI.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/Platform/OpenGL/OpenGLRendererAPI.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/Platform/OpenGL/OpenGLShader.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/Platform/OpenGL/OpenGLShader.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/Platform/OpenGL/OpenGLTexture.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/Platform/OpenGL/OpenGLTexture.cpp")




add_library(legacy SHARED ${HEADERS} ${SOURCES} 
                         ${IMGUI_FILES} ${OPENGL}
                         ${STB_IMG_FILES})

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

# message("DIR  ${CMAKE_SOURCE_DIR}/src")

# message("all header files: ${HEADERS}")