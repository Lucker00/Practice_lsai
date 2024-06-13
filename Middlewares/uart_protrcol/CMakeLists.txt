cmake_minimum_required(VERSION 3.22)

project(uart_protrcol)
add_library(uart_protrcol INTERFACE)

# Enable CMake support for ASM and C languages
enable_language(C ASM)

# target_compile_definitions(app INTERFACE 
#     $<$<CONFIG:Debug>:DEBUG>
# )


target_include_directories(uart_protrcol INTERFACE
    ./
)


target_sources(uart_protrcol INTERFACE
    protocol.c
    ring_buffer.c
)


# target_link_libraries(uart_protrcol PRIVATE
#     stm32cubemx
#     system
# )

# target_link_libraries(stm32cubemx INTERFACE
# )

# Validate that STM32CubeMX code is compatible with C standard
if(CMAKE_C_STANDARD LESS 11)
    message(ERROR "Generated code requires C11 or higher")
endif()


