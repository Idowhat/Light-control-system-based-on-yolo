

#include "./BSP/ATK_MW8266D/atk_mw8266d_uart.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>              
           
static uint8_t g_uart_tx_buf[ATK_MW8266D_UART_TX_BUF_SIZE]; /* ATK-MW8266D UART发送缓冲 */

/**
 * @brief       ATK-MW8266D UART printf
 * @param       fmt: 待打印的数据
 * @retval      无
 */
void atk_mw8266d_uart_printf(char *fmt, ...)
{
    va_list ap;
    uint16_t len;
    
    va_start(ap, fmt);
    vsprintf((char *)g_uart_tx_buf, fmt, ap);
    va_end(ap);
    
    len = strlen((const char *)g_uart_tx_buf);
    HAL_UART_Transmit(&g_uart1_handle, g_uart_tx_buf, len, HAL_MAX_DELAY);
		while(__HAL_UART_GET_FLAG(&g_uart1_handle, UART_FLAG_TC) != SET);  
}

/**
 * @brief       ATK-MW8266D UART重新开始接收数据
 * @param       无
 * @retval      无
 */
void atk_mw8266d_uart_rx_restart(void)
{
    g_usart_rx_sta =0 ;
}

/**
 * @brief       获取ATK-MW8266D UART接收到的一帧数据
 * @param       无
 * @retval      NULL: 未接收到一帧数据
 *              其他: 接收到的一帧数据
 */
uint8_t *atk_mw8266d_uart_rx_get_frame(void)
{
    if (g_usart_rx_sta & 0x8000)
    {		
        g_usart_rx_buf[g_usart_rx_sta & 0x3fff] = '\0';
        return g_usart_rx_buf;
    }
    else
    {
        return NULL;
    }
}

/**
 * @brief       获取ATK-MW8266D UART接收到的一帧数据的长度
 * @param       无
 * @retval      0   : 未接收到一帧数据
 *              其他: 接收到的一帧数据的长度
 */
uint16_t atk_mw8266d_uart_rx_get_frame_len(void)
{
    if (g_usart_rx_sta & 0x8000)
    {
        return g_usart_rx_sta & 0x3fff;
    }
    else
    {
        return 0;
    }
}







