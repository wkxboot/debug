#ifndef  __LOG_UART_H__
#define  __LOG_UART_H__

#ifdef   __cplusplus
#define  LOG_UART_BEGIN        extern "C" {
#define  LOG_UART_END          }
#else
#define  LOG_UART_BEGIN      
#define  LOG_UART_END        
#endif

#include "stdint.h"

#define  LOG_UART_RX_BUFFER_SIZE              32
#define  LOG_UART_TX_BUFFER_SIZE              4096


#define  LOG_UART_PORT                        1
#define  LOG_UART_BAUD_RATES                  115200
#define  LOG_UART_DATA_BITS                   8
#define  LOG_UART_STOP_BITS                   1

/*
* @brief 串口uart初始化
* @param 无
* @return =0 成功
* @return <0 失败
* @note
*/

int log_uart_init(void);

/*
* @brief 串口uart读取数据
* @param dst 读取的数据存储的目的地
* @param size 期望读取的数量
* @return  实际读取的数量
* @note
*/

uint32_t log_uart_read(char *dst,uint32_t size);

/*
* @brief 串口uart写入数据
* @param src 写入的数据的源地址
* @param size 期望写入的数量
* @return  实际写入的数量
* @note
*/

uint32_t log_uart_write(char *src,uint32_t size);

/*
* @brief log 串口中断
* @param 无
* @param 无
* @return 无
* @note
*/
void log_uart_isr();

LOG_UART_END



#endif

