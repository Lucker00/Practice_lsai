/*
 * @Author: error: error: git config user.name & please set dead value or install git && error: git config user.email & please set dead value or install git & please set dead value or install git
 * @Date: 2024-05-28 10:31:06
 * @LastEditors: error: error: git config user.name & please set dead value or install git && error: git config user.email & please set dead value or install git & please set dead value or install git
 * @LastEditTime: 2024-05-28 22:15:11
 * @FilePath: /stm32_test/driver/bsp/include/timer.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#pragma once
#include "sys.h"

/****************************************************************************************************/
/* 通用定时器 定义 */

/* TIMX 中断定义 
 * 默认是针对TIM2~TIM5
 * 注意: 通过修改这4个宏定义,可以支持TIM1~TIM8任意一个定时器.
 */
 
#define GTIM_TIMX_INT                       TIM3
#define GTIM_TIMX_INT_IRQn                  TIM3_IRQn
#define GTIM_TIMX_INT_IRQHandler            TIM3_IRQHandler
#define GTIM_TIMX_INT_CLK_ENABLE()          do{ __HAL_RCC_TIM3_CLK_ENABLE(); }while(0)   /* TIM3 时钟使能 */

/* TIMX 输入捕获定义
 * 这里的输入捕获使用定时器TIM5_CH1,捕获WK_UP按键的输入
 * 默认是针对TIM2~TIM5.
 * 注意: 通过修改这几个宏定义,可以支持TIM1~TIM8任意一个定时器,任意一个IO口做输入捕获
 *       特别要注意:默认用的PA0,设置的是下拉输入!如果改其他IO,对应的上下拉方式也得改!
 */
#define GTIM_TIMX_CAP_CHY_GPIO_PORT GPIOA
#define GTIM_TIMX_CAP_CHY_GPIO_PIN GPIO_PIN_0
#define GTIM_TIMX_CAP_CHY_GPIO_CLK_ENABLE() \
    do                                      \
    {                                       \
        __HAL_RCC_GPIOA_CLK_ENABLE();       \
    } while (0)                                 /* PA口时钟使能 */
#define GTIM_TIMX_CAP_CHY_GPIO_AF GPIO_AF2_TIM5 /* AF功能选择 */


#define GTIM_TIMX_CAP                       TIM5
#define GTIM_TIMX_CAP_IRQn                  TIM5_IRQn
#define GTIM_TIMX_CAP_IRQHandler            TIM5_IRQHandler
#define GTIM_TIMX_CAP_CHY                   TIM_CHANNEL_1   /* 通道Y,  1<= Y <=4 */
#define GTIM_TIMX_CAP_CHY_CCRX              TIM5->CCR1 /* 通道Y的输出比较寄存器 */
#define GTIM_TIMX_CAP_CHY_CLK_ENABLE() \
    do                                 \
    {                                  \
        __HAL_RCC_TIM5_CLK_ENABLE();   \
    } while (0) /* TIM5 时钟使能 */

#define GTIM_TIMX_CAP_CHY_CLK_DISABLE()     \
    do                                      \
    {                                       \
        __HAL_RCC_TIM5_CLK_DISABLE();       \
    } while (0) /* TIM5 时钟使能 */



#define HIGH_LEVEL_COUNT_MAX  20
#define LOW_LEVEL_COUNT_MAX  20
typedef struct timer_record
{
    uint8_t start_raise_flag;
    uint32_t high_level_time[HIGH_LEVEL_COUNT_MAX];
    uint8_t high_level_count;
    uint32_t low_level_time[LOW_LEVEL_COUNT_MAX];
    uint8_t low_level_count;
}timer_record;




void gtim_timx_int_init(uint16_t arr, uint16_t psc);        /* 通用定时器 定时中断初始化函数 */
// void gtim_timx_pwm_chy_init(uint16_t arr, uint16_t psc);    /* 通用定时器 PWM初始化函数 */
void gtim_timx_cap_chy_init(uint32_t arr, uint16_t psc, uint8_t capPolarity); /* 通用定时器 输入捕获初始化函数 */

extern volatile unsigned long long FreeRTOSRunTimeTicks;
void ConfigureTimeForRunTimeStats(void);
