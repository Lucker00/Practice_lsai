/*
 * @Author: listenai_fhhao fhhao@listenai.com
 * @Date: 2024-04-30 10:52:46
 * @LastEditors: listenai_fhhao fhhao@listenai.com
 * @LastEditTime: 2024-05-02 22:11:51
 * @FilePath: /stm32_test/driver/bsp/include/tpl0401.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#pragma once
#include "sys.h"


/******************************************************************************************/


#define TPL_POWER_PORT                  GPIOB
#define TPL_POWER_PIN                   GPIO_PIN_9
#define TPL_POWER_CLK_ENABLE()          do{ __HAL_RCC_GPIOB_CLK_ENABLE(); }while(0)




#define TPL0401_POWER(x)   do{ x ? \
                      HAL_GPIO_WritePin(TPL_POWER_PORT, TPL_POWER_PIN, GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(TPL_POWER_PORT, TPL_POWER_PIN, GPIO_PIN_RESET); \
                  }while(0)


void tpl0401_init(void); 


/**************    CONSTANTS, MACROS, & DATA STRUCTURES    ***************/
#define TPL0401_DEBUG 0

#define TPL0401_I2C_SLAVE_ADDRESS 0x3E
#define TPL0401_NORMAL_WORK_STEP 11

#define TPL0401_MINI_STEP 5
#define TPL0401_MAX_STEP 127
#define TPL0401_STEP_END (TPL0401_MAX_STEP+1)


/***********************    FUNCTION PROTOTYPES    ***********************/

int TPL0401Init(uint8_t default_step);
int TPL0401SetWiperStep(uint8_t step);

uint8_t tpl0401_get_step(void) ;

