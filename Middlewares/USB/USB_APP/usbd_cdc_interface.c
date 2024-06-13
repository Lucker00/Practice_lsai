/**
 ****************************************************************************************************
 * @file        usbd_cdc_interface.c
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2022-01-20
 * @brief       USB CDC ��������
 * @license     Copyright (c) 2020-2032, ������������ӿƼ����޹�˾
 ****************************************************************************************************
 * @attention
 *
 * ʵ��ƽ̨:����ԭ�� STM32F407������
 * ������Ƶ:www.yuanzige.com
 * ������̳:www.openedv.com
 * ��˾��ַ:www.alientek.com
 * �����ַ:openedv.taobao.com
 *
 * �޸�˵��
 * V1.0 20220120
 * ��һ�η���
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


/* USB���⴮��������ò��� */
USBD_CDC_LineCodingTypeDef LineCoding =
{
    115200,     /* ������ */
    0x00,       /* ֹͣλ,Ĭ��1λ */
    0x00,       /* У��λ,Ĭ���� */
    0x08        /* ����λ,Ĭ��8λ */
};


// /* usb_printf���ͻ�����, ����vsprintf */
uint8_t g_usb_usart_printf_buffer[USB_USART_REC_LEN];

/* USB���յ����ݻ�����,���USART_REC_LEN���ֽ�,����USBD_CDC_SetRxBuffer���� */
uint8_t g_usb_rx_buffer[USB_USART_REC_LEN];
extern SemaphoreHandle_t xSem_USB_receive;

/* �����ƴ���1�������ݵķ���,������USB���⴮�ڽ��յ������� */
// uint8_t g_usb_usart_rx_buffer[USB_USART_REC_LEN];       /* ���ջ���,���USART_REC_LEN���ֽ� */




extern USBD_HandleTypeDef USBD_Device;
static int8_t CDC_Itf_Init(void);
static int8_t CDC_Itf_DeInit(void);
static int8_t CDC_Itf_Control(uint8_t cmd, uint8_t *pbuf, uint16_t length);
static int8_t CDC_Itf_Receive(uint8_t *pbuf, uint32_t *Len);
static int8_t CDC_Itf_TransmitCplt(uint8_t *Buf, uint32_t *Len, uint8_t epnum);


/* ���⴮�����ú���(��USB�ں˵���) */
USBD_CDC_ItfTypeDef USBD_CDC_fops =
{
    CDC_Itf_Init,
    CDC_Itf_DeInit,
    CDC_Itf_Control,
    CDC_Itf_Receive,
    CDC_Itf_TransmitCplt
};

/**
 * @brief       ��ʼ�� CDC
 * @param       ��
 * @retval      USB״̬
 *   @arg       USBD_OK(0)   , ����;
 *   @arg       USBD_BUSY(1) , æ;
 *   @arg       USBD_FAIL(2) , ʧ��;
 */
static int8_t CDC_Itf_Init(void)
{
    USBD_memset(g_usb_rx_buffer, 0, sizeof(g_usb_rx_buffer));
    USBD_CDC_SetRxBuffer(&USBD_Device, g_usb_rx_buffer);
    return USBD_OK;
}

/**
 * @brief       ��λ CDC
 * @param       ��
 * @retval      USB״̬
 *   @arg       USBD_OK(0)   , ����;
 *   @arg       USBD_BUSY(1) , æ;
 *   @arg       USBD_FAIL(2) , ʧ��;
 */
static int8_t CDC_Itf_DeInit(void)
{
    return USBD_OK;
}

/**
 * @brief       ���� CDC ������
 * @param       cmd     : ��������
 * @param       buf     : �������ݻ�����/�������滺����
 * @param       length  : ���ݳ���
 * @retval      USB״̬
 *   @arg       USBD_OK(0)   , ����;
 *   @arg       USBD_BUSY(1) , æ;
 *   @arg       USBD_FAIL(2) , ʧ��;
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
            /* ��ӡ���ò��� */
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
 * @brief       CDC ���ݽ��պ���
 * @param       buf     : �������ݻ�����
 * @param       len     : ���յ������ݳ���
 * @retval      USB״̬
 *   @arg       USBD_OK(0)   , ����;
 *   @arg       USBD_BUSY(1) , æ;
 *   @arg       USBD_FAIL(2) , ʧ��;
 */
static int8_t CDC_Itf_Receive(uint8_t *buf, uint32_t *len)
{
    USBD_CDC_ReceivePacket(&USBD_Device);
    if(xSem_USB_receive){
        pcl_data_input(buf, *len, false);

        BaseType_t xHigherPriorityTaskWoken; 
        // ��ʼ������ΪpdFALSE
        xHigherPriorityTaskWoken = pdFALSE; 
        // ����FreeRTOS������ע�⴫�ݱ����ĵ�ַ
        xSemaphoreGiveFromISR( xSem_USB_receive, &xHigherPriorityTaskWoken ); 
        // ���xHigherPriorityTaskWoken����ΪpdTRUE����ô�����ISR��
        // �����ź���ʱ��һ�����񱻻���
        if( xHigherPriorityTaskWoken )
        {
            // ʵ����Ҫ������������л�
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
 * @brief       ͨ�� USB ��������
 * @param       buf     : Ҫ���͵����ݻ�����
 * @param       len     : ���ݳ���
 * @retval      ��
 */
int cdc_vcp_data_tx(uint8_t *data, uint32_t Len)
{
    USBD_CDC_SetTxBuffer(&USBD_Device, data, Len);
    USBD_CDC_TransmitPacket(&USBD_Device);
    delay_ms(CDC_POLLING_INTERVAL);
    return 0;
}

/**
 * @brief       ͨ�� USB ��ʽ���������
 *   @note      ͨ��USB VCPʵ��printf���
 *              ȷ��һ�η������ݳ��Ȳ��� USB_USART_REC_LEN �ֽ�
 * @param       ��ʽ�����
 * @retval      ��
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
    i = strlen((const char *)g_usb_usart_printf_buffer);    /* �˴η������ݵĳ��� */
    cdc_vcp_data_tx(g_usb_usart_printf_buffer, i);          /* �������� */
}











