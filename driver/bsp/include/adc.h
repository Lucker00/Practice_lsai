
#pragma once
#include "sys.h"


/******************************************************************************************/
/* ADC及引脚 定义 */

#define ADC_ADCX_CHY_GPIO_PORT              GPIOC
#define ADC_ADCX_CHY_GPIO_PIN               GPIO_PIN_2
#define ADC_ADCX_CHY_GPIO_CLK_ENABLE()      do{ __HAL_RCC_GPIOC_CLK_ENABLE(); }while(0)         /* PC口时钟使能 */

#define ADC_ADCX                            ADC1
#define ADC_ADCX_CHY                        ADC_CHANNEL_12                                       /* 通道Y,  0 <= Y <= 17 */ 
#define ADC_ADCX_CHY_CLK_ENABLE()           do{ __HAL_RCC_ADC1_CLK_ENABLE(); }while(0)          /* ADC1 时钟使能 */


#define ADC_MA_DETECT_PORT                      GPIOC
#define ADC_MA_DETECT_PIN                       GPIO_PIN_0
#define ADC_MA_DETECT_GPIO_CLK_ENABLE()      do{ __HAL_RCC_GPIOC_CLK_ENABLE(); }while(0)         /* PC口时钟使能 */

#define ADC_MA_DETECT                            ADC1
#define ADC_MA_DETECT_CHY                        ADC_CHANNEL_10                                       /* 通道Y,  0 <= Y <= 17 */ 
#define ADC_MA_DETECT_CHY_CLK_ENABLE()           do{ __HAL_RCC_ADC1_CLK_ENABLE(); }while(0)          /* ADC1 时钟使能 */

#define ADC_UA_DETECT_PORT                      GPIOC
#define ADC_UA_DETECT_PIN                       GPIO_PIN_1
#define ADC_UA_DETECT_GPIO_CLK_ENABLE()      do{ __HAL_RCC_GPIOC_CLK_ENABLE(); }while(0)         /* PC口时钟使能 */

#define ADC_UA_DETECT                            ADC1
#define ADC_UA_DETECT_CHY                        ADC_CHANNEL_11                                       /* 通道Y,  0 <= Y <= 17 */ 
#define ADC_UA_DETECT_CHY_CLK_ENABLE()           do{ __HAL_RCC_ADC1_CLK_ENABLE(); }while(0)          /* ADC1 时钟使能 */



/******************************************************************************************/

void adc_init(void);                                            /* ADC初始化 */
void adc_channel_set(ADC_HandleTypeDef *adc_handle, uint32_t ch, uint32_t rank, uint32_t stime); /* ADC通道设置 */
uint32_t adc_get_result(uint32_t ch);                           /* 获得某个通道值 */
uint32_t adc_get_result_average(uint32_t ch, uint8_t times);    /* 得到某个通道给定次数采样的平均值 */


uint32_t adc_ua_get_result_average(uint32_t ch, uint8_t times);    /* 得到某个通道给定次数采样的平均值 */
uint32_t adc_ma_get_result_average(uint32_t ch, uint8_t times);    /* 得到某个通道给定次数采样的平均值 */
