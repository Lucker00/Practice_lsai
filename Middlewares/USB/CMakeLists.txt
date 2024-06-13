cmake_minimum_required(VERSION 3.22)

project(usb)
add_library(usb INTERFACE)

# Enable CMake support for ASM and C languages
enable_language(C ASM)

# target_compile_definitions(app INTERFACE 
#     $<$<CONFIG:Debug>:DEBUG>
# )


target_include_directories(usb INTERFACE
    STM32_USB_Device_Library/Core/Inc
    STM32_USB_Device_Library/Class/CDC/Inc
    USB_APP/


)


target_sources(usb INTERFACE
    STM32_USB_Device_Library/Core/Src/usbd_core.c
    STM32_USB_Device_Library/Core/Src/usbd_ctlreq.c
    STM32_USB_Device_Library/Core/Src/usbd_ioreq.c
    STM32_USB_Device_Library/Class/CDC/Src/usbd_cdc.c
    USB_APP/usbd_cdc_interface.c
    USB_APP/usbd_conf.c
    USB_APP/usbd_desc.c
)


target_link_libraries(usb INTERFACE
    stm32cubemx
    system
    malloc
    uart_protrcol
    freertos
)

# target_link_libraries(stm32cubemx INTERFACE
# )

# Validate that STM32CubeMX code is compatible with C standard
if(CMAKE_C_STANDARD LESS 11)
    message(ERROR "Generated code requires C11 or higher")
endif()


