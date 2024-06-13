cmake_minimum_required(VERSION 3.22)

project(system)
add_library(system INTERFACE)

# Enable CMake support for ASM and C languages
enable_language(C ASM)

# target_compile_options(system INTERFACE -Wno-unused-parameter)

target_include_directories(system INTERFACE
    delay/
    sys/
    usart/
)


target_sources(system INTERFACE
    delay/delay.c
    sys/sys.c
    usart/usart.c
)


# target_link_libraries(stm32cubemx INTERFACE
# )

# Validate that STM32CubeMX code is compatible with C standard
if(CMAKE_C_STANDARD LESS 11)
    message(ERROR "Generated code requires C11 or higher")
endif()


