cmake_minimum_required(VERSION 3.0.0)
project(Glad)

set(GLAD_HD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include/glad/glad.h"
                "${CMAKE_CURRENT_SOURCE_DIR}/include/KHR/khrplatform.h")
set(GLAD_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/glad.c")

add_library(Glad STATIC ${GLAD_SRC_DIR} ${GLAD_SRC_DIR} )

# //Compiling with -fPIC (force position independent code)
target_compile_options(Glad PRIVATE -fPIC) #Option 1

# set_property(TARGET Glad PROPERTY POSITION_INDEPENDENT_CODE ON) #Option 2