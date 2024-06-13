cmake_minimum_required(VERSION 3.22)

project(bsp)
add_library(bsp INTERFACE)

# Enable CMake support for ASM and C languages
enable_language(C ASM)

# target_compile_definitions(app INTERFACE 
#     $<$<CONFIG:Debug>:DEBUG>
# )


target_include_directories(bsp INTERFACE
    ./include/
)


target_sources(bsp INTERFACE
    ./src/control_io.c
    ./src/control_remote_key.c
    ./src/timer.c
    ./src/pwmdac.c
    ./src/adc.c
    ./src/key.c
    ./src/myiic.c
    ./src/tpl0401.c
)


# Add linked libraries
target_link_libraries(bsp INTERFACE
    stm32cubemx
    system
)



# Validate that STM32CubeMX code is compatible with C standard
if(CMAKE_C_STANDARD LESS 11)
    message(ERROR "Generated code requires C11 or higher")
endif()


