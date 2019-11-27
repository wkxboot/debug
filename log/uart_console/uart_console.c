/**
******************************************************************************                                                                                                                                                       
*                                                                            
*  This program is free software; you can redistribute it and/or modify      
*  it under the terms of the GNU General Public License version 3 as         
*  published by the Free Software Foundation.                                
*                                                                            
*  @file       uart_console.c
*  @brief      uart_console
*  @author     wkxboot
*  @version    v1.0.0
*  @date       2019/6/22
*  @copyright  <h4><left>&copy; copyright(c) 2019 wkxboot 1131204425@qq.com</center></h4>  
*                                                                            
*                                                                            
*****************************************************************************/
#include "uart_console.h"

/** 日志串口句柄*/
xuart_handle_t uart_console_handle;

#define  UART_CONSOLE_ISR  st_uart_hal_isr

/**
* @brief 串口uart初始化
* @param 无
* @return 无
* @note
*/
void uart_console_init(void)
{
    int rc;

    uart_console_handle = xuart_create(UART_CONSOLE_RX_BUFFER_SIZE,UART_CONSOLE_TX_BUFFER_SIZE,&st_cm3_xuart_hal_driver);
    DEBUG_ASSERT(uart_console_handle);
   
    rc = xuart_open(uart_console_handle,UART_CONSOLE_PORT,UART_CONSOLE_BAUD_RATES,UART_CONSOLE_DATA_BITS,UART_CONSOLE_STOP_BITS);
    DEBUG_ASSERT(rc == XUART_ERROR_OK);
    (void)rc;
}

/**
* @brief 串口uart读取数据
* @param dst 读取的数据存储的目的地
* @param size 期望读取的数量
* @return  实际读取的数量
* @note
*/
uint32_t uart_console_read(char *dst,uint32_t size)
{
    return xuart_read(uart_console_handle,(uint8_t *)dst,size);
}

/**
* @brief 串口uart写入数据
* @param src 写入的数据的源地址
* @param size 期望写入的数量
* @return  实际写入的数量
* @note
*/
uint32_t uart_console_write(char *src,uint32_t size)
{
    uint32_t write_size;

    write_size = xuart_write(uart_console_handle,(uint8_t *)src,size); 

    return write_size;
}