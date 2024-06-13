/*
 * @Author: listenai_fhhao fhhao@listenai.com
 * @Date: 2024-05-01 12:11:41
 * @LastEditors: listenai_fhhao fhhao@listenai.com
 * @LastEditTime: 2024-05-06 16:57:06
 * @FilePath: /stm32_test/driver/bsp/include/control_remote_key.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#pragma once
#include "sys.h"
#include <stdint.h>


typedef struct{
    uint32_t key_pin;
    GPIO_TypeDef* key_port;
    uint8_t key_status;
}key_info_t;



#define REMOTE_KEY_CONTROL_IO_CLK_ENABLE()          do{ __HAL_RCC_GPIOA_CLK_ENABLE(); \
                                                        __HAL_RCC_GPIOB_CLK_ENABLE(); \
                                                        __HAL_RCC_GPIOC_CLK_ENABLE(); \
                                                        __HAL_RCC_GPIOD_CLK_ENABLE(); \
                                                        __HAL_RCC_GPIOE_CLK_ENABLE(); }while(0)


#define REMOTE_KEY_PRESS  1
#define REMOTE_KEY_RELEASE 0


#define REMOTE_KEY_COUNT  42

/******************************************************************************************/
void control_key_init(void);

int control_key(uint8_t key, uint8_t status);

int key_status_printf(void);


