/*
 * @Author: listenai_fhhao fhhao@listenai.com
 * @Date: 2024-04-24 14:38:42
 * @LastEditors: listenai_fhhao fhhao@listenai.com
 * @LastEditTime: 2024-05-02 17:46:37
 * @FilePath: /stm32_test/driver/bsp/include/control_io.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#pragma once
#include "sys.h"
#include <stdint.h>


// #define LED0_TOGGLE()    do{ HAL_GPIO_TogglePin(LED0_GPIO_PORT, LED0_GPIO_PIN); }while(0)       /* LED0 = !LED0 */
// #define LED1_TOGGLE()    do{ HAL_GPIO_TogglePin(LED1_GPIO_PORT, LED1_GPIO_PIN); }while(0)       /* LED1 = !LED1 */

/******************************************************************************************/

// 其他旁路电路控制开关，睡眠模式采样电流时，需要关闭其他旁路电路
#define OTHER_CIRCUIT_CONTROL_PORT                  GPIOB
#define OTHER_CIRCUIT_CONTROL_PIN                   GPIO_PIN_3
#define OTHER_CIRCUIT_CONTROL_CLK_ENABLE()          do{ __HAL_RCC_GPIOB_CLK_ENABLE(); }while(0)

// 采样电路的控制开关：  0: 连接旁路  1: 断开旁路
#define OTHER_CIRCUIT_CONT(x)   do{ x ? \
                      HAL_GPIO_WritePin(OTHER_CIRCUIT_CONTROL_PORT, OTHER_CIRCUIT_CONTROL_PIN, GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(OTHER_CIRCUIT_CONTROL_PORT, OTHER_CIRCUIT_CONTROL_PIN, GPIO_PIN_RESET); \
                  }while(0)



#define CURRENT_ADC_MODE_PORT                  GPIOB
#define CURRENT_ADC_MODE_PIN                   GPIO_PIN_5
#define CURRENT_ADC_MODE_CLK_ENABLE()          do{ __HAL_RCC_GPIOB_CLK_ENABLE(); }while(0)

// 采样电路的控制开关：  1: 运行模式  0: 睡眠模式
#define CURRENT_ADC_MODE(x)   do{ x ? \
                      HAL_GPIO_WritePin(CURRENT_ADC_MODE_PORT, CURRENT_ADC_MODE_PIN, GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(CURRENT_ADC_MODE_PORT, CURRENT_ADC_MODE_PIN, GPIO_PIN_RESET); \
                  }while(0)

#define REMOTE_POWER_CONTROL_PORT                  GPIOB
#define REMOTE_POWER_CONTROL_PIN                   GPIO_PIN_9
#define REMOTE_POWER_CONTROL_CLK_ENABLE()          do{ __HAL_RCC_GPIOB_CLK_ENABLE(); }while(0)

// 遥控器电源的上电开关
#define REMOTE_POWER_CONTROL(x)   do{ x ? \
                      HAL_GPIO_WritePin(REMOTE_POWER_CONTROL_PORT, REMOTE_POWER_CONTROL_PIN, GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(REMOTE_POWER_CONTROL_PORT, REMOTE_POWER_CONTROL_PIN, GPIO_PIN_RESET); \
                  }while(0)



/******************************************************************************************/
void detect_current_mode_init(void); 

/* 
*  param: mode:0 / 1, 具体含义如下:
*  0: 睡眠电流采样模式
*  1：工作电流采样模式
* * */
void detect_current_mode(uint8_t mode); 


