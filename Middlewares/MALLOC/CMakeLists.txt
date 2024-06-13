cmake_minimum_required(VERSION 3.22)

project(malloc)
add_library(malloc INTERFACE)

# Enable CMake support for ASM and C languages
enable_language(C ASM)

# target_compile_definitions(app INTERFACE 
#     $<$<CONFIG:Debug>:DEBUG>
# )


target_include_directories(malloc INTERFACE
    ./
)


target_sources(malloc INTERFACE
    malloc.c
)


target_link_libraries(malloc INTERFACE
    stm32cubemx
    system
)

# target_link_libraries(stm32cubemx INTERFACE
# )

# Validate that STM32CubeMX code is compatible with C standard
if(CMAKE_C_STANDARD LESS 11)
    message(ERROR "Generated code requires C11 or higher")
endif()


