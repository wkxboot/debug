#ifndef  __LOG_H__
#define  __LOG_H__
 
#ifdef  __cplusplus
#define  LOG_BEGIN extern "C" {
#define  LOG_END   }
#else
#define  LOG_BEGIN
#define  LOG_END
#endif
 
LOG_BEGIN

#include "stdarg.h"
#include "stdint.h"
#include "string.h"
#include "printf.h"

#define  LOG_LEVEL_OFF             0U
#define  LOG_LEVEL_ERROR           1U
#define  LOG_LEVEL_WARNING         2U
#define  LOG_LEVEL_INFO            3U
#define  LOG_LEVEL_DEBUG           4U
#define  LOG_LEVEL_LOWEST          4U


/******************************************************************************/
/*    配置开始                                                                */
/******************************************************************************/
#define  LOG_PRINTF_BUFFER_SIZE    256
#define  LOG_LEVEL_GLOBLE_DEFAULT  LOG_LEVEL_DEBUG 
#define  LOG_USE_SEGGER_RTT        1/*segger_rtt输出/如果选项为真则uart失效*/
#define  LOG_USE_UART_CONSOLE      1/*uart输出*/
#define  LOG_USE_COLORS            0
#define  LOG_USE_TIMESTAMP         0
#define  LOG_USE_FILE_NAME         0
#define  LOG_USE_LINE_NAME         0
#define  LOG_USE_LEVEL_INFO        1
/******************************************************************************/
/*    配置结束                                                                */
/******************************************************************************/
#define  LOG_COLOR_BLACK           "\x1B[2;30m"
#define  LOG_COLOR_RED             "\x1B[2;31m"
#define  LOG_COLOR_GREEN           "\x1B[2;32m"
#define  LOG_COLOR_YELLOW          "\x1B[2;33m"
#define  LOG_COLOR_BLUE            "\x1B[2;34m"
#define  LOG_COLOR_MAGENTA         "\x1B[2;35m"
#define  LOG_COLOR_CYAN            "\x1B[2;36m"
#define  LOG_COLOR_WHITE           "\x1B[2;37m"

#if  LOG_USE_COLORS > 0
#define  LOG_ERROR_COLOR           LOG_COLOR_RED
#define  LOG_WARNING_COLOR         LOG_COLOR_MAGENTA
#define  LOG_INFO_COLOR            LOG_COLOR_YELLOW
#define  LOG_DEBUG_COLOR           LOG_COLOR_GREEN
#else
#define LOG_ERROR_COLOR
#define LOG_WARNING_COLOR
#define LOG_INFO_COLOR
#define LOG_DEBUG_COLOR 
#endif 

#if  LOG_USE_TIMESTAMP > 0
#define  LOG_TIMESTAMP_FORMAT  "[%8d]"
#define  LOG_TIMESTAMP_VALUE   ,log_time()
#else
#define  LOG_TIMESTAMP_FORMAT
#define  LOG_TIMESTAMP_VALUE
#endif

#if  LOG_USE_LEVEL_INFO > 0
#define  LOG_ERROR_LEVEL_INFO    "[error]"
#define  LOG_WARNING_LEVEL_INFO  "[warning]"
#define  LOG_INFO_LEVEL_INFO     "[info]"
#define  LOG_DEBUG_LEVEL_INFO    "[debug]"
#else
#define  LOG_ERROR_LEVEL_INFO
#define  LOG_WARNING_LEVEL_INFO
#define  LOG_INFO_LEVEL_INFO
#define  LOG_DEBUG_LEVEL_INFO
#endif

#if  LOG_USE_FILE_NAME > 0
#define  LOG_FILE_NAME_FORMAT  "[%s]"
#define  LOG_FILE_NAME         ,__FILE__
#else
#define LOG_FILE_NAME_FORMAT
#define  LOG_FILE_NAME
#endif

#if  LOG_USE_LINE_NAME > 0
#define  LOG_LINE_NUM_FORMAT   "[%d]"
#define  LOG_LINE_NAME         ,__LINE__
#else
#define  LOG_LINE_NUM_FORMAT
#define  LOG_LINE_NAME
#endif

#define  LOG_PREFIX_VALUE  LOG_TIMESTAMP_VALUE LOG_FILE_NAME LOG_LINE_NAME

#define  LOG_ERROR_PREFIX_FORMAT   LOG_ERROR_COLOR   LOG_TIMESTAMP_FORMAT LOG_ERROR_LEVEL_INFO   LOG_FILE_NAME_FORMAT LOG_LINE_NUM_FORMAT
#define  LOG_WARNING_PREFIX_FORMAT LOG_WARNING_COLOR LOG_TIMESTAMP_FORMAT LOG_WARNING_LEVEL_INFO LOG_FILE_NAME_FORMAT LOG_LINE_NUM_FORMAT
#define  LOG_INFO_PREFIX_FORMAT    LOG_INFO_COLOR    LOG_TIMESTAMP_FORMAT LOG_INFO_LEVEL_INFO    LOG_FILE_NAME_FORMAT LOG_LINE_NUM_FORMAT
#define  LOG_DEBUG_PREFIX_FORMAT   LOG_DEBUG_COLOR   LOG_TIMESTAMP_FORMAT LOG_DEBUG_LEVEL_INFO   LOG_FILE_NAME_FORMAT LOG_LINE_NUM_FORMAT



/**
* @brief 终端日志初始化
* @param 无
* @return 无
* @note
*/
void log_init(void);


/**
* @brief 日志时间
* @param 无
* @return 
* @note 日志时间
*/
uint32_t log_time(void);

/**
* @brief 终端读取输入
* @param dst 读取数据存储的目的地址
* @param size 期望读取的数量
* @return 实际读取的数量
* @note
*/
uint32_t log_read(char *dst,uint32_t size);

/**
* @brief 设置日志全局输出等级
* @param lelvel 日志等级
* @return = 0 成功
* @return < 0 失败
* @note level >= LOG_LEVEL_OFF && level <=LOG_LEVEL_ARRAY
*/
int log_set_level(uint8_t level);

/**
* @brief 终端日志输出
* @param level 输出等级
* @param format 格式化字符串
* @param ... 可变参数
* @return 实际写入的数量
* @note
*/
int log_printf(uint8_t level,const char *format,...);

/*
* @brief 日志debug输出
* @param format格式化字符串
* @param ...可变参数
* @return 无
* @note 
*/
#define  log_debug(format,arg...)                                                          \
{                                                                                          \
   log_printf(LOG_LEVEL_DEBUG,LOG_DEBUG_PREFIX_FORMAT format LOG_PREFIX_VALUE,##arg);      \
}

/*
* @brief 日志info输出
* @param format格式化字符串
* @param ...可变参数
* @return 无
* @note 
*/
#define  log_info(format,arg...)                                                           \
{                                                                                          \
   log_printf(LOG_LEVEL_INFO,LOG_INFO_PREFIX_FORMAT format LOG_PREFIX_VALUE,##arg);        \
}

/*
* @brief 日志warning输出
* @param format格式化字符串
* @param ...可变参数
* @return 无
* @note 
*/
#define  log_warning(format,arg...)                                                        \
{                                                                                          \
   log_printf(LOG_LEVEL_WARNING,LOG_WARNING_PREFIX_FORMAT format LOG_PREFIX_VALUE,##arg);  \
}

/*
* @brief 日志error输出
* @param format格式化字符串
* @param ...可变参数
* @return 无
* @note   
*/
#define  log_error(format,arg...)                                                           \
{                                                                                           \
   log_printf(LOG_LEVEL_ERROR,LOG_ERROR_PREFIX_FORMAT format LOG_PREFIX_VALUE,##arg);       \
}

/*
* @brief 日志断言
* @param 无
* @return 
* @note 
*/ 
void log_assert_handler(int line,char *file_name);


/*
* @brief 终端日志断言空指针
* @param expr 断言变量
* @return 无
* @note
*/
#define log_assert(expr)                                           \
{                                                                  \
    if ((void *)(expr) == (void *)0) {                             \
        log_assert_handler(__LINE__,__FILE__);	                   \
    }                                                              \
}

LOG_END

#endif