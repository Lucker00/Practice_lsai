/*
 * @Author: error: error: git config user.name & please set dead value or install git && error: git config user.email & please set dead value or install git & please set dead value or install git
 * @Date: 2024-05-30 11:40:37
 * @LastEditors: error: error: git config user.name & please set dead value or install git && error: git config user.email & please set dead value or install git & please set dead value or install git
 * @LastEditTime: 2024-05-31 17:12:55
 * @FilePath: /my_stm32_test/app/main.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "sys.h"
#include "usart.h"
#include "delay.h"


// #include "adc.h"
// #include "key.h"
// #include "control_io.h"
// #include "tpl0401.h"
// #include "control_remote_key.h"
// #include "public_func.h"

// #include "usbd_core.h"
// #include "usbd_desc.h"
// #include "usbd_cdc.h"
// #include "usbd_cdc_interface.h"

#include <stdint.h>
#include <stdio.h>
#include "string.h"
#include "FreeRTOS.h"
#include "task.h"

#include "timer.h"
#include "task_event.h"

// #include "log.h"

#define  FIRST_TASK_SIZE 128
extern void usart_init(uint32_t baudrate);

extern void task_keypad(void *pvParameters);
extern void task_infrared(void *pvParameters);
extern void task_uart(void *pvParameters);
void first_task(void *pvParameters);

int main(){
    HAL_Init();
    usart_init(115200);
    xTaskCreate((TaskHookFunction_t) first_task, "first_task", FIRST_TASK_SIZE, NULL, 1, NULL);
}

void first_task(void *pvParameters){

    xTaskCreate((TaskHookFunction_t) task_uart, "task_uart", 128, NULL, 2, NULL);
    xTaskCreate((TaskHookFunction_t) task_keypad, "task_keypad", 128, NULL, 3, NULL);
    xTaskCreate((TaskHookFunction_t) task_infrared, "task_infrared", 128, NULL, 3, NULL);
    

    
    while(1){
        // printf("first_task\r\n");
        // vTaskDelay(1000);
    }
}