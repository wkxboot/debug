/*****************************************************************************
*  serial uart                                                               
*  Copyright (C) 2019 wkxboot 1131204425@qq.com.                             
*                                                                            
*                                                                            
*  This program is free software; you can redistribute it and/or modify      
*  it under the terms of the GNU General Public License version 3 as         
*  published by the Free Software Foundation.                                
*                                                                            
*  @file     log_uart.c                                                      
*  @brief    日志uart实现                                                    
*  @author   wkxboot                                                         
*  @email    1131204425@qq.com                                               
*  @version  v1.0.0                                                          
*  @date     2019/1/10                                                       
*  @license  GNU General Public License (GPL)                                
*                                                                            
*                                                                            
*****************************************************************************/
#include "st_cm3_uart_hal_driver.h"
#include "xuart.h"
#include "log_uart.h"

/*日志串口句柄*/
xuart_handle_t log_uart_handle;
/*日志接收和发送缓存*/
static uint8_t log_recv_buffer[LOG_UART_RX_BUFFER_SIZE];
static uint8_t log_send_buffer[LOG_UART_TX_BUFFER_SIZE];

extern void st_uart_hal_isr(xuart_handle_t *handle);
#define  UART_ISR  st_uart_hal_isr
/*
* @brief 串口uart初始化
* @param 无
* @return 0：成功 -1：失败
* @note
*/
int log_uart_init(void)
{
    int rc;
    rc = xuart_open(&log_uart_handle,LOG_UART_PORT,LOG_UART_BAUD_RATES,LOG_UART_DATA_BITS,LOG_UART_STOP_BITS,
                     log_recv_buffer, LOG_UART_RX_BUFFER_SIZE,log_send_buffer, LOG_UART_TX_BUFFER_SIZE);
    if (rc != 0) {
        return -1;
    }

    return 0;
}

/*
* @brief 串口uart读取数据
* @param dst 读取的数据存储的目的地
* @param size 期望读取的数量
* @return  实际读取的数量
* @note
*/
uint32_t log_uart_read(char *dst,uint32_t size)
{
    return xuart_read(&log_uart_handle,(uint8_t *)dst,size);
}

/*
* @brief 串口uart写入数据
* @param src 写入的数据的源地址
* @param size 期望写入的数量
* @return  实际写入的数量
* @note
*/
uint32_t log_uart_write(char *src,uint32_t size)
{
    uint32_t write_size;

    write_size = xuart_write(&log_uart_handle,(uint8_t *)src,size); 

    return write_size;
}

/*
* @brief log 串口中断
* @param 无
* @param 无
* @return 无
* @note
*/
void log_uart_isr()
{
    UART_ISR(&log_uart_handle);
}


