cmake_minimum_required(VERSION 3.5)

set(LKGUI_SOURCE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/LkGui/src/LkGui")
set(SOURCE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/LkGui/src")
set(LKGUI_LIBS "${CMAKE_SOURCE_DIR}/lib")
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "GLFW lib only")
set(GLFW_BUILD_TESTS OFF CACHE BOOL "GLFW lib only")
set(GLFW_BUILD_DOCS OFF CACHE BOOL "GLFW lib only")
set(GLFW_BUILD_INSTALL OFF CACHE BOOL "GLFW lib only")

project(LkGui LANGUAGES C ASM)

list(APPEND CMAKE_MODULE_PATH
        "${CMAKE_SOURCE_DIR}/cmake"
)
find_package(GLFW3 REQUIRED)

add_executable(${PROJECT_NAME} "${SOURCE_PATH}/main.c")

add_subdirectory(lib)
include(${SOURCE_PATH}/CMakeLists.txt)

target_compile_definitions(${PROJECT_NAME}
    PUBLIC
        LK_IMPL_OPENGL_GLAD
        _DEBUG
)

#target_sources(${PROJECT_NAME}
#    PUBLIC	${LKGUI_SOURCE_PATH}/LkGui.h
#        ${LKGUI_SOURCE_PATH}/LkGui.c
#)


target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${SOURCE_PATH}
        ${LKGUI_SOURCE_PATH}
        ${CMAKE_CURRENT_LIST_DIR}/lib
        ${LKGUI_LIBS}/glad/include
        ${GLFW3_INCLUDE_DIR}
        ${PROJECT_SOURCE_DIR}/LkGui/src/LkGui/Backends
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        ${GLFW3_LIBRARY}
        cglm
)

file(COPY assets/ DESTINATION ${CMAKE_BINARY_DIR}/assets)

include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
