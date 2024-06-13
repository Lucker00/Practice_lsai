/**
 ****************************************************************************************************
 * @file        usbd_cdc_interface.c
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

#include "string.h"
#include "stdarg.h"
#include "stdio.h"
#include "usbd_cdc_interface.h"
#include "usart.h"
#include "delay.h"
#include "protocol.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include <stdint.h>


/* USB虚拟串口相关配置参数 */
USBD_CDC_LineCodingTypeDef LineCoding =
{
    115200,     /* 波特率 */
    0x00,       /* 停止位,默认1位 */
    0x00,       /* 校验位,默认无 */
    0x08        /* 数据位,默认8位 */
};


// /* usb_printf发送缓冲区, 用于vsprintf */
uint8_t g_usb_usart_printf_buffer[USB_USART_REC_LEN];

/* USB接收的数据缓冲区,最大USART_REC_LEN个字节,用于USBD_CDC_SetRxBuffer函数 */
uint8_t g_usb_rx_buffer[USB_USART_REC_LEN];
extern SemaphoreHandle_t xSem_USB_receive;

/* 用类似串口1接收数据的方法,来处理USB虚拟串口接收到的数据 */
// uint8_t g_usb_usart_rx_buffer[USB_USART_REC_LEN];       /* 接收缓冲,最大USART_REC_LEN个字节 */




extern USBD_HandleTypeDef USBD_Device;
static int8_t CDC_Itf_Init(void);
static int8_t CDC_Itf_DeInit(void);
static int8_t CDC_Itf_Control(uint8_t cmd, uint8_t *pbuf, uint16_t length);
static int8_t CDC_Itf_Receive(uint8_t *pbuf, uint32_t *Len);
static int8_t CDC_Itf_TransmitCplt(uint8_t *Buf, uint32_t *Len, uint8_t epnum);


/* 虚拟串口配置函数(供USB内核调用) */
USBD_CDC_ItfTypeDef USBD_CDC_fops =
{
    CDC_Itf_Init,
    CDC_Itf_DeInit,
    CDC_Itf_Control,
    CDC_Itf_Receive,
    CDC_Itf_TransmitCplt
};

/**
 * @brief       初始化 CDC
 * @param       无
 * @retval      USB状态
 *   @arg       USBD_OK(0)   , 正常;
 *   @arg       USBD_BUSY(1) , 忙;
 *   @arg       USBD_FAIL(2) , 失败;
 */
static int8_t CDC_Itf_Init(void)
{
    USBD_memset(g_usb_rx_buffer, 0, sizeof(g_usb_rx_buffer));
    USBD_CDC_SetRxBuffer(&USBD_Device, g_usb_rx_buffer);
    return USBD_OK;
}

/**
 * @brief       复位 CDC
 * @param       无
 * @retval      USB状态
 *   @arg       USBD_OK(0)   , 正常;
 *   @arg       USBD_BUSY(1) , 忙;
 *   @arg       USBD_FAIL(2) , 失败;
 */
static int8_t CDC_Itf_DeInit(void)
{
    return USBD_OK;
}

/**
 * @brief       控制 CDC 的设置
 * @param       cmd     : 控制命令
 * @param       buf     : 命令数据缓冲区/参数保存缓冲区
 * @param       length  : 数据长度
 * @retval      USB状态
 *   @arg       USBD_OK(0)   , 正常;
 *   @arg       USBD_BUSY(1) , 忙;
 *   @arg       USBD_FAIL(2) , 失败;
 */
static int8_t CDC_Itf_Control(uint8_t cmd, uint8_t *pbuf, uint16_t length)
{
    switch (cmd)
    {
        case CDC_SEND_ENCAPSULATED_COMMAND:
            break;

        case CDC_GET_ENCAPSULATED_RESPONSE:
            break;

        case CDC_SET_COMM_FEATURE:
            break;

        case CDC_GET_COMM_FEATURE:
            break;

        case CDC_CLEAR_COMM_FEATURE:
            break;

        case CDC_SET_LINE_CODING:
            CLOG_HEX_DUMP("CDC_SET_LINE_CODING", pbuf, length);
            LineCoding.bitrate = (uint32_t) (pbuf[0] | (pbuf[1] << 8) |
                                             (pbuf[2] << 16) | (pbuf[3] << 24));
            LineCoding.format = pbuf[4];
            LineCoding.paritytype = pbuf[5];
            LineCoding.datatype = pbuf[6];
            /* 打印配置参数 */
            CLOGD("linecoding.format:%d", LineCoding.format);
            CLOGD("linecoding.paritytype:%d", LineCoding.paritytype);
            CLOGD("linecoding.datatype:%d", LineCoding.datatype);
            CLOGD("linecoding.bitrate:%ld", LineCoding.bitrate);
            pcl_reset();
            break;

        case CDC_GET_LINE_CODING:
            pbuf[0] = (uint8_t) (LineCoding.bitrate);
            pbuf[1] = (uint8_t) (LineCoding.bitrate >> 8);
            pbuf[2] = (uint8_t) (LineCoding.bitrate >> 16);
            pbuf[3] = (uint8_t) (LineCoding.bitrate >> 24);
            pbuf[4] = LineCoding.format;
            pbuf[5] = LineCoding.paritytype;
            pbuf[6] = LineCoding.datatype;
            break;

        case CDC_SET_CONTROL_LINE_STATE:
            break;

        case CDC_SEND_BREAK:
            break;

        default:
            break;
    }

    return USBD_OK;
}

/**
 * @brief       CDC 数据接收函数
 * @param       buf     : 接收数据缓冲区
 * @param       len     : 接收到的数据长度
 * @retval      USB状态
 *   @arg       USBD_OK(0)   , 正常;
 *   @arg       USBD_BUSY(1) , 忙;
 *   @arg       USBD_FAIL(2) , 失败;
 */
static int8_t CDC_Itf_Receive(uint8_t *buf, uint32_t *len)
{
    USBD_CDC_ReceivePacket(&USBD_Device);
    if(xSem_USB_receive){
        pcl_data_input(buf, *len, false);

        BaseType_t xHigherPriorityTaskWoken; 
        // 初始化变量为pdFALSE
        xHigherPriorityTaskWoken = pdFALSE; 
        // 调用FreeRTOS函数，注意传递变量的地址
        xSemaphoreGiveFromISR( xSem_USB_receive, &xHigherPriorityTaskWoken ); 
        // 如果xHigherPriorityTaskWoken现在为pdTRUE，那么在这个ISR中
        // 给出信号量时有一个任务被唤醒
        if( xHigherPriorityTaskWoken )
        {
            // 实际上要求进行上下文切换
            portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
        }
    }
    return USBD_OK;
}

static int8_t CDC_Itf_TransmitCplt(uint8_t *Buf, uint32_t *Len, uint8_t epnum)
{
    // transmit complete
    // printf("CDC_Itf_TransmitCplt,transmit complete\n");
    return USBD_OK;
}



/**
 * @brief       通过 USB 发送数据
 * @param       buf     : 要发送的数据缓冲区
 * @param       len     : 数据长度
 * @retval      无
 */
int cdc_vcp_data_tx(uint8_t *data, uint32_t Len)
{
    USBD_CDC_SetTxBuffer(&USBD_Device, data, Len);
    USBD_CDC_TransmitPacket(&USBD_Device);
    delay_ms(CDC_POLLING_INTERVAL);
    return 0;
}

/**
 * @brief       通过 USB 格式化输出函数
 *   @note      通过USB VCP实现printf输出
 *              确保一次发送数据长度不超 USB_USART_REC_LEN 字节
 * @param       格式化输出
 * @retval      无
 */
extern volatile uint8_t g_device_state;
void usb_printf(char *fmt, ...)
{
    if(!g_device_state)
    {
        return;
    }
    uint16_t i;
    va_list ap;
    va_start(ap, fmt);
    vsprintf((char *)g_usb_usart_printf_buffer, fmt, ap);
    va_end(ap);
    i = strlen((const char *)g_usb_usart_printf_buffer);    /* 此次发送数据的长度 */
    cdc_vcp_data_tx(g_usb_usart_printf_buffer, i);          /* 发送数据 */
}











