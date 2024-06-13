/**
 * @file log.h
 * @author TsMax (dske@listenai.com)
 * @brief 
 * @version 0.1
 * @date 2024-05-13
 * 
 * @copyright Copyright (c) 2021 - 2024 shenzhen listenai co., ltd.
 * 
 * SPDX-License-Identifier: Apache-2.0
 */

/**************************************/
#ifndef __LOG_H__
#define __LOG_H__
/**************************************/

#include "stdio.h"
#include "stdarg.h"
#include "stdint.h"
#include "string.h"
#include <stdio.h>

#define LOG_UART

#if defined(LOG_UART)
#define LOG_PRINTF printf
#define CLOG(fmt, ...) LOG_PRINTF(fmt "\n" LOG_RESET_COLOR, ##__VA_ARGS__)

#elif defined(LOG_RTT)
#define LOG_PRINTF(fmt, ...) SEGGER_RTT_printf(0, fmt, ##__VA_ARGS__)
#define CLOG(fmt, ...) SEGGER_RTT_printf(0, fmt "\n" LOG_RESET_COLOR, ##__VA_ARGS__)

#elif defined(LOG_CDC)
#define LOG_PRINTF usb_printf
#define CLOG(fmt, ...) usb_printf(fmt "\n" LOG_RESET_COLOR, ##__VA_ARGS__)

#else
#define LOG_PRINTF
#define CLOG(fmt, ...)
#endif

#define CLOG_LEVEL_NONE 0
#define CLOG_LEVEL_ERROR 1
#define CLOG_LEVEL_WARN 2
#define CLOG_LEVEL_INFO 3
#define CLOG_LEVEL_DEBUG 4
#define CLOG_LEVEL_VERBOSE 5

#define CLOG_LEVEL CLOG_LEVEL_DEBUG

#define CONFIG_LOG_COLORS 1

/* clang-format off */
#if CONFIG_LOG_COLORS
#define LOG_COLOR_BLACK   "30"
#define LOG_COLOR_RED     "31"
#define LOG_COLOR_GREEN   "32"
#define LOG_COLOR_BROWN   "33"
#define LOG_COLOR_BLUE    "34"
#define LOG_COLOR_PURPLE  "35"
#define LOG_COLOR_CYAN    "36"
#define LOG_COLOR(COLOR)  "\033[0;" COLOR "m"
#define LOG_BOLD(COLOR)   "\033[1;" COLOR "m"
#define LOG_RESET_COLOR   "\033[0m"
#define LOG_COLOR_E       LOG_COLOR(LOG_COLOR_RED)
#define LOG_COLOR_W       LOG_COLOR(LOG_COLOR_BROWN)
#define LOG_COLOR_I       LOG_COLOR(LOG_COLOR_GREEN)
#define LOG_COLOR_D
#define LOG_COLOR_V
#else /* CONFIG_LOG_COLORS */
#define LOG_COLOR_E
#define LOG_COLOR_W
#define LOG_COLOR_I
#define LOG_COLOR_D
#define LOG_COLOR_V
#define LOG_COLOR(COLOR)
#define LOG_RESET_COLOR
#endif /* CONFIG_LOG_COLORS */


#define CLOGE(fmt, ...)     do {if (CLOG_LEVEL >= CLOG_LEVEL_ERROR)  { CLOG(LOG_COLOR_E "ERR:"fmt,##__VA_ARGS__);}} while(0)
#define CLOGW(fmt, ...)     do {if (CLOG_LEVEL >= CLOG_LEVEL_WARN)   { CLOG(LOG_COLOR_W "WRN:"fmt,##__VA_ARGS__);}} while(0)
#define CLOGI(fmt, ...)     do {if (CLOG_LEVEL >= CLOG_LEVEL_INFO)   { CLOG(LOG_COLOR_I "INF:"fmt,##__VA_ARGS__);}} while(0)
#define CLOGD(fmt, ...)     do {if (CLOG_LEVEL >= CLOG_LEVEL_DEBUG)  { CLOG("DBG:"fmt,##__VA_ARGS__);}} while(0)
#define CLOGV(fmt, ...)     do {if (CLOG_LEVEL >= CLOG_LEVEL_VERBOSE){ CLOG("VBS:"fmt,##__VA_ARGS__);}} while(0)


void log_hexdump(const char *TAG, uint8_t *buf, uint32_t length);


#define CLOG_HEX_DUMP(TAG, buf, length) log_hexdump(TAG, buf, length)


#endif /* LOG_H */