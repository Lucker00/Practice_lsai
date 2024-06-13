cmake_minimum_required(VERSION 3.22)

project(stm32cubemx)
add_library(stm32cubemx INTERFACE)

target_compile_options(stm32cubemx INTERFACE -Wno-unused-parameter)

# Enable CMake support for ASM and C languages
enable_language(C ASM)

target_compile_definitions(stm32cubemx INTERFACE 
	USE_HAL_DRIVER 
	STM32F407xx
    USE_USB_FS
    $<$<CONFIG:Debug>:DEBUG>
)

target_include_directories(stm32cubemx INTERFACE
    ../../Core/Inc
    ../../driver/CMSIS/Include
    ../../driver/CMSIS/Device/ST/STM32F4xx/Include
    ../../driver/STM32F4xx_HAL_Driver/Inc
    ../../driver/STM32F4xx_HAL_Driver/Inc/Legacy
)

target_sources(stm32cubemx INTERFACE
    ../../driver/CMSIS/Device/ST/STM32F4xx/Source/Templates/gcc/startup_stm32f407xx.s
    ../../Core/Src/system_stm32f4xx.c
    ../../Core/Src/stm32f4xx_it.c
    ../../driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim.c
    ../../driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim_ex.c
    ../../driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_uart.c
    ../../driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc.c
    ../../driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc_ex.c
    ../../driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash.c
    ../../driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ex.c
    ../../driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ramfunc.c
    ../../driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio.c
    ../../driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma_ex.c
    ../../driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma.c
    ../../driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr.c
    ../../driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr_ex.c
    ../../driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cortex.c
    ../../driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.c
    ../../driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_exti.c
    ../../driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_adc.c
    ../../driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_adc_ex.c
    ../../driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_usb.c
    ../../driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pcd.c
    ../../driver/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pcd_ex.c
)


# target_link_libraries(stm32cubemx INTERFACE
# )

# Validate that STM32CubeMX code is compatible with C standard
if(CMAKE_C_STANDARD LESS 11)
    message(ERROR "Generated code requires C11 or higher")
endif()



