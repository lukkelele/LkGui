target_sources(${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/LkGui/LkGui.h
        ${CMAKE_CURRENT_LIST_DIR}/LkGui/LkGui.c
        ${CMAKE_CURRENT_LIST_DIR}/LkGui/LkGui_Internal.h
)

include(${CMAKE_CURRENT_LIST_DIR}/LkGui/Core/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/LkGui/Backends/CMakeLists.txt)
