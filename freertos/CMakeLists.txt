cmake_minimum_required(VERSION 3.22)

project(freertos)
add_library(freertos INTERFACE)

# Enable CMake support for ASM and C languages
enable_language(C ASM)

# target_compile_definitions(app INTERFACE 
#     $<$<CONFIG:Debug>:DEBUG>
# )


target_include_directories(freertos INTERFACE
    include/
    portable/MemMang/
    portable/GCC/ARM_CM4F/
)


target_sources(freertos INTERFACE
    portable/MemMang/heap_4.c
    portable/GCC/ARM_CM4F/port.c
    croutine.c
    event_groups.c
    list.c
    queue.c
    tasks.c
    timers.c
)


# target_link_libraries(stm32cubemx INTERFACE
# )

# Validate that STM32CubeMX code is compatible with C standard
if(CMAKE_C_STANDARD LESS 11)
    message(ERROR "Generated code requires C11 or higher")
endif()


add_compile_options(-D__forceinline=inline)

