cmake_minimum_required(VERSION 3.22)

project(RTT)
add_library(RTT INTERFACE)

# Enable CMake support for ASM and C languages
enable_language(C ASM)

# target_compile_definitions(app INTERFACE 
#     $<$<CONFIG:Debug>:DEBUG>
# )


target_include_directories(RTT INTERFACE
    ./
)


target_sources(RTT INTERFACE
    SEGGER_RTT_printf.c
    SEGGER_RTT.c
)




# target_link_libraries(stm32cubemx INTERFACE
# )

# Validate that STM32CubeMX code is compatible with C standard
if(CMAKE_C_STANDARD LESS 11)
    message(ERROR "Generated code requires C11 or higher")
endif()


