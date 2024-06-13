/*
 * @Author: listenai_fhhao fhhao@listenai.com
 * @Date: 2024-04-30 13:48:16
 * @LastEditors: listenai_fhhao fhhao@listenai.com
 * @LastEditTime: 2024-05-02 19:33:53
 * @FilePath: /stm32_test/Middlewares/USB/USB_APP/usbd_cdc_interface.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
/**
 ****************************************************************************************************
 * @file        usbd_cdc_interface.h
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2022-01-20
 * @brief       USB CDC 驱动代码
 * @license     Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ****************************************************************************************************
 * @attention
 *
 * 实验平台:正点原子 STM32F407开发板
 * 在线视频:www.yuanzige.com
 * 技术论坛:www.openedv.com
 * 公司网址:www.alientek.com
 * 购买地址:openedv.taobao.com
 *
 * 修改说明
 * V1.0 20220120
 * 第一次发布
 *
 ****************************************************************************************************
 */

#ifndef __USBD_CDC_IF_H
#define __USBD_CDC_IF_H

#include "usbd_cdc.h"


#define USB_USART_REC_LEN       256     /* USB串口接收缓冲区最大字节数 */

/* 轮询周期，最大65ms，最小1ms */
#define CDC_POLLING_INTERVAL    1       /* 轮询周期，最大65ms，最小1ms */

// extern uint8_t  g_usb_usart_rx_buffer[USB_USART_REC_LEN];   /* 接收缓冲,最大USB_USART_REC_LEN个字节.末字节为换行符 */
extern uint16_t g_usb_usart_rx_sta;                         /* 接收状态标记 */

extern USBD_CDC_ItfTypeDef  USBD_CDC_fops;


int cdc_vcp_data_tx(uint8_t *buf,uint32_t len);
void cdc_vcp_data_rx(uint8_t* buf, uint32_t len);
void usb_printf(char* fmt,...); 

#endif 

