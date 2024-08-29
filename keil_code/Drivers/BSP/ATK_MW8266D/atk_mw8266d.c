

#include "./BSP/ATK_MW8266D/atk_mw8266d.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"
#include <string.h>
#include <stdio.h>
#include "./BSP/IWDG/iwdg.h"




/**
 * @brief       ATK-MW8266D硬件初始化
 * @param       无
 * @retval      无
 */


void atk_mw8266d_hw_init(void)
{
    GPIO_InitTypeDef gpio_init_struct;
    
    ATK_MW8266D_RST_GPIO_CLK_ENABLE();
    
    gpio_init_struct.Pin = ATK_MW8266D_RST_GPIO_PIN;
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;
    gpio_init_struct.Pull = GPIO_NOPULL;
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(ATK_MW8266D_RST_GPIO_PORT, &gpio_init_struct);
}




/**
 * @brief       ATK-MW8266D硬件复位
 * @param       无
 * @retval      无
 */
 
 
 
void atk_mw8266d_hw_reset(void)
{
    ATK_MW8266D_RST(0);
    delay_ms(100);
    ATK_MW8266D_RST(1);
    delay_ms(500);
}





/**
 * @brief       ATK-MW8266D发送AT指令
 * @param       cmd    : 待发送的AT指令
 *              ack    : 等待的响应
 *              timeout: 等待超时时间
 * @retval      ATK_MW8266D_EOK     : 函数执行成功
 *              ATK_MW8266D_ETIMEOUT: 等待期望应答超时，函数执行失败
 */
uint8_t atk_mw8266d_send_at_cmd(char *cmd, char *ack, uint32_t timeout)
{
    uint8_t *ret = NULL;
    
    atk_mw8266d_uart_rx_restart();
    atk_mw8266d_uart_printf("%s\r\n", cmd);
    
    if ((ack == NULL) || (timeout == 0))
    {
        return ATK_MW8266D_EOK;
    }
    else
    {
        while (timeout > 0)
        {
            ret = atk_mw8266d_uart_rx_get_frame();
            if (ret != NULL)
            {
                if (strstr((const char *)ret, ack) != NULL)
                {
                    return ATK_MW8266D_EOK;
                }
                else
                {
                    atk_mw8266d_uart_rx_restart();
                }
            }
            timeout--;
            delay_ms(1);
        }
        
        return ATK_MW8266D_ETIMEOUT;
    }
}


/**
 * @brief       ATK-MW8266D恢复出厂设置
 * @param       无
 * @retval      ATK_MW8266D_EOK  : 恢复出场设置成功
 *              ATK_MW8266D_ERROR: 恢复出场设置失败
 */
uint8_t atk_mw8266d_restore(void)
{
    uint8_t ret;
    
    ret = atk_mw8266d_send_at_cmd("AT+RESTORE", "ready", 3000);
    if (ret == ATK_MW8266D_EOK)
    {
        return ATK_MW8266D_EOK;
    }
    else
    {
        return ATK_MW8266D_ERROR;
    }
}

/**
 * @brief       ATK-MW8266D AT指令测试
 * @param       无
 * @retval      ATK_MW8266D_EOK  : AT指令测试成功
 *              ATK_MW8266D_ERROR: AT指令测试失败
 */
uint8_t atk_mw8266d_at_test(void)
{
    uint8_t ret;
    uint8_t i;
    
    for (i=0; i<10; i++)
    {
        ret = atk_mw8266d_send_at_cmd("AT", "OK", 500);
        if (ret == ATK_MW8266D_EOK)
        {
            return ATK_MW8266D_EOK;
        }
    }
    
    return ATK_MW8266D_ERROR;
}

/**
 * @brief       设置ATK-MW8266D工作模式
 * @param       mode: 1，Station模式
 *                    2，AP模式
 *                    3，AP+Station模式
 * @retval      ATK_MW8266D_EOK   : 工作模式设置成功
 *              ATK_MW8266D_ERROR : 工作模式设置失败
 *              ATK_MW8266D_EINVAL: mode参数错误，工作模式设置失败
 */
uint8_t atk_mw8266d_set_mode(uint8_t mode)
{
    uint8_t ret;
    
    switch (mode)
    {
        case 1:
        {
            ret = atk_mw8266d_send_at_cmd("AT+CWMODE=1", "OK", 500);    /* Station模式 */
            break;
        }
        case 2:
        {
            ret = atk_mw8266d_send_at_cmd("AT+CWMODE=2", "OK", 500);    /* AP模式 */
            break;
        }
        case 3:
        {
            ret = atk_mw8266d_send_at_cmd("AT+CWMODE=3", "OK", 500);    /* AP+Station模式 */
            break;
        }
        default:
        {
            return ATK_MW8266D_EINVAL;
        }
    }
    
    if (ret == ATK_MW8266D_EOK)
    {
        return ATK_MW8266D_EOK;
    }
    else
    {
        return ATK_MW8266D_ERROR;
    }
}

/**
 * @brief       ATK-MW8266D软件复位
 * @param       无
 * @retval      ATK_MW8266D_EOK  : 软件复位成功
 *              ATK_MW8266D_ERROR: 软件复位失败
 */
uint8_t atk_mw8266d_sw_reset(void)
{
    uint8_t ret;
    
    ret = atk_mw8266d_send_at_cmd("AT+RST", "OK", 500);
    if (ret == ATK_MW8266D_EOK)
    {
        return ATK_MW8266D_EOK;
    }
    else
    {
        return ATK_MW8266D_ERROR;
    }
}

/**
 * @brief       ATK-MW8266D设置回显模式
 * @param       cfg: 0，关闭回显
 *                   1，打开回显
 * @retval      ATK_MW8266D_EOK  : 设置回显模式成功
 *              ATK_MW8266D_ERROR: 设置回显模式失败
 */
uint8_t atk_mw8266d_ate_config(uint8_t cfg)
{
    uint8_t ret;
    
    switch (cfg)
    {
        case 0:
        {
            ret = atk_mw8266d_send_at_cmd("ATE0", "OK", 500);   /* 关闭回显 */
            break;
        }
        case 1:
        {
            ret = atk_mw8266d_send_at_cmd("ATE1", "OK", 500);   /* 打开回显 */
            break;
        }
        default:
        {
            return ATK_MW8266D_EINVAL;
        }
    }
    
    if (ret == ATK_MW8266D_EOK)
    {
        return ATK_MW8266D_EOK;
    }
    else
    {
        return ATK_MW8266D_ERROR;
    }
}

/**
 * @brief       ATK-MW8266D连接WIFI
 * @param       ssid: WIFI名称
 *              pwd : WIFI密码
 * @retval      ATK_MW8266D_EOK  : WIFI连接成功
 *              ATK_MW8266D_ERROR: WIFI连接失败
 */
uint8_t atk_mw8266d_join_ap(char *ssid, char *pwd)
{
    uint8_t ret;
    char cmd[64];
    
    sprintf(cmd, "AT+CWJAP=\"%s\",\"%s\"", ssid, pwd);
    ret = atk_mw8266d_send_at_cmd(cmd, "WIFI GOT IP", 10000);
    if (ret == ATK_MW8266D_EOK)
    {
        return ATK_MW8266D_EOK;
    }
    else
    {
        return ATK_MW8266D_ERROR;
    }
}

/**
 * @brief       ATK-MW8266D获取IP地址
 * @param       buf: IP地址，需要16字节内存空间
 * @retval      ATK_MW8266D_EOK  : 获取IP地址成功
 *              ATK_MW8266D_ERROR: 获取IP地址失败
 */
uint8_t atk_mw8266d_get_ip(char *buf)
{
    uint8_t ret;
    char *p_start;
    char *p_end;
    
    ret = atk_mw8266d_send_at_cmd("AT+CIFSR", "OK", 500);
    if (ret != ATK_MW8266D_EOK)
    {
        return ATK_MW8266D_ERROR;
    }
    
    p_start = strstr((const char *)atk_mw8266d_uart_rx_get_frame(), "\"");
    p_end = strstr(p_start + 1, "\"");
    *p_end = '\0';
    sprintf(buf, "%s", p_start + 1);
    
    return ATK_MW8266D_EOK;
}

/**
 * @brief       ATK-MW8266D连接TCP服务器
 * @param       server_ip  : TCP服务器IP地址
 *              server_port: TCP服务器端口号
 * @retval      ATK_MW8266D_EOK  : 连接TCP服务器成功
 *              ATK_MW8266D_ERROR: 连接TCP服务器失败
 */
uint8_t atk_mw8266d_connect_tcp_server(char *server_ip, char *server_port)
{
    uint8_t ret;
    char cmd[64];
    
    sprintf(cmd, "AT+CIPSTART=\"TCP\",\"%s\",%s", server_ip, server_port);
    ret = atk_mw8266d_send_at_cmd(cmd, "CONNECT", 5000);
    if (ret == ATK_MW8266D_EOK)
    {
        return ATK_MW8266D_EOK;
    }
    else
    {
        return ATK_MW8266D_ERROR;
    }
}

/**
 * @brief       ATK-MW8266D进入透传
 * @param       无
 * @retval      ATK_MW8266D_EOK  : 进入透传成功
 *              ATK_MW8266D_ERROR: 进入透传失败
 */
uint8_t atk_mw8266d_enter_unvarnished(void)
{
    uint8_t ret;
    
    ret  = atk_mw8266d_send_at_cmd("AT+CIPMODE=1", "OK", 500);
    ret += atk_mw8266d_send_at_cmd("AT+CIPSEND", ">", 500);
    if (ret == ATK_MW8266D_EOK)
    {
        return ATK_MW8266D_EOK;
    }
    else
    {
        return ATK_MW8266D_ERROR;
    }
}

/**
 * @brief       ATK-MW8266D退出透传
 * @param       无
 * @retval      无
 */
void atk_mw8266d_exit_unvarnished(void)
{
    atk_mw8266d_uart_printf("+++");
}

/**
 * @brief       ATK-MW8266D连接原子云服务器
 * @param       id : 原子云设备编号
 *              pwd: 原子云设备密码
 * @retval      ATK_MW8266D_EOK  : 连接原子云服务器成功
 *              ATK_MW8266D_ERROR: 连接原子云服务器失败
 */
uint8_t atk_mw8266d_connect_atkcld(char *id, char *pwd)
{
    uint8_t ret;
    char cmd[64];
    
    sprintf(cmd, "AT+ATKCLDSTA=\"%s\",\"%s\"", id, pwd);
    ret = atk_mw8266d_send_at_cmd(cmd, "CLOUD CONNECTED", 3000);
    if (ret == ATK_MW8266D_EOK)
    {
        return ATK_MW8266D_EOK;
    }
    else
    {
        return ATK_MW8266D_ERROR;
    }
}


uint8_t atk_mw8266d_send_disconnect(char *cmd, char *ack,char *error , uint32_t timeout)
{
    uint8_t *ret = NULL;
    uint8_t  first_char=0x01;
    atk_mw8266d_uart_rx_restart();
    atk_mw8266d_uart_printf("%s\r\n", cmd);
    
    if ((ack == NULL) || (timeout == 0))
    {
        return ATK_MW8266D_EOK;
    }
    else
    {
        while (timeout > 0)
        {
            ret = atk_mw8266d_uart_rx_get_frame();
            if (ret != NULL)
            {
                if (strstr((const char *)ret, ack) != NULL)
                {
										
									first_char='\0';
									atk_mw8266d_uart_rx_restart();
									
                }
								
								else
                {
                    atk_mw8266d_uart_rx_restart();
                }
								
								
								if (( first_char=='\0')&(strstr((const char *)ret,error) != NULL))
										return ATK_MW8266D_EOK;
                
            }
            timeout--;
            delay_ms(1);
        }
        
        return ATK_MW8266D_ETIMEOUT;
    }
}






/**
 * @brief       ATK-MW8266D断开原子云服务器连接
 * @param       无
 * @retval      ATK_MW8266D_EOK  : 断开原子云服务器连接成功
 *              ATK_MW8266D_ERROR: 断开原子云服务器连接失败
 */
uint8_t atk_mw8266d_disconnect_atkcld(void)
{
    uint8_t ret;
    
    //ret = atk_mw8266d_send_disconnect("AT+ATKCLDCLS", "\0","ERROR", 500);
			ret = atk_mw8266d_send_at_cmd("AT+ATKCLDCLS", "\0", 500);
    if (ret == ATK_MW8266D_EOK)
    {
        return ATK_MW8266D_EOK;
    }
    else
    {
        return ATK_MW8266D_ETIMEOUT;
    }
}



/**
 * @brief       ATK-MW8266D接收命令并核对命令内容
 * @param       ack    : 要核对的内容
 * @retval      ATK_MW8266D_EOK     : 收到的内容跟核对内容一致
 *              ATK_MW8266D_ERROR: 内容不同
 */
uint8_t atk_mw8266d_check_act(char *ack)
{
	
	
	
    uint8_t *ret = NULL;
    ret = atk_mw8266d_uart_rx_get_frame();
    if (strstr((const char *)ret, ack) != NULL)
      {												
         return EQUAL;
      }
    else
      {
				return	UNEQUAL;
      }
           
	
}


/**
 * @brief       保持ATK-MW8266D的原子云连接
 * @param       void
 * @retval      void         
 */
void atk_mw8266d_keep_connect(void)//暂时放弃此函数
{
	
	
																																			
   /*uint8_t ret;
   ret = atk_mw8266d_send_at_cmd("AT", "OK", 300);		//此方案还是有问题，还是会断开连接。
	 if (ret == ATK_MW8266D_EOK) //说明断开原子云连接，进行重连	
    {
			
			ret = atk_mw8266d_connect_atkcld(DEMO_ATKCLD_DEV_ID, DEMO_ATKCLD_DEV_PWD);				
			if (ret!=ATK_MW8266D_EOK)
			{
			while(1)
			{	
			ret = atk_mw8266d_connect_atkcld(DEMO_ATKCLD_DEV_ID, DEMO_ATKCLD_DEV_PWD);		
			if(ret==ATK_MW8266D_EOK)
				break;	
			LED0(0);
			delay_ms(200);	
			LED0(1);
			delay_ms(200);	
			}
			}  
    }*/
		
		//atk_mw8266d_connect_atkcld(DEMO_ATKCLD_DEV_ID, DEMO_ATKCLD_DEV_PWD);//新方案，每隔五分钟发送一次连接命令。保证连接（方案失败）
		//atk_mw8266d_connect_atkcld(DEMO_ATKCLD_DEV_ID, DEMO_ATKCLD_DEV_PWD);
		//atk_mw8266d_connect_atkcld(DEMO_ATKCLD_DEV_ID, DEMO_ATKCLD_DEV_PWD);
		
   	
}



/**
 * @brief       上电连接原子云
 * @param       void
 * @retval      void            
 */


void  connect_atkcld (void)
{		
		uint8_t ret=ATK_MW8266D_ERROR;
		uint8_t connect_sta=ATK_MW8266D_ETIMEOUT;
		connect_sta=atk_mw8266d_disconnect_atkcld();
		if (connect_sta==ATK_MW8266D_ETIMEOUT)
		{	
			while(1)
			{connect_sta=atk_mw8266d_disconnect_atkcld();
				
				if(connect_sta==ATK_MW8266D_EOK)
				{break;}
					LED0(0);
					delay_ms(200);	
					LED0(1);
				
			}
		
		}
		if(connect_sta==ATK_MW8266D_EOK)
	
		{
					ret = atk_mw8266d_connect_atkcld(DEMO_ATKCLD_DEV_ID, DEMO_ATKCLD_DEV_PWD);
					if (ret!=ATK_MW8266D_EOK)
					{
					while(1)
					{
					ret = atk_mw8266d_connect_atkcld(DEMO_ATKCLD_DEV_ID, DEMO_ATKCLD_DEV_PWD);
					if(ret==ATK_MW8266D_EOK)
						break;	
					LED0(0);
					delay_ms(1000);	
					LED0(1);
					
					}
					}
				}

}
