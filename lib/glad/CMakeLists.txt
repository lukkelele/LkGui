target_sources(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_SOURCE_DIR}/lib/glad/include/glad/glad.h
        ${CMAKE_SOURCE_DIR}/lib/glad/include/KHR/khrplatform.h
        ${CMAKE_SOURCE_DIR}/lib/glad/src/glad.c
)
