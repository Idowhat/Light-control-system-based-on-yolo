
#include "./BSP/Trigger/Trigger.h"
#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"
#include "./BSP/IWDG/iwdg.h"
#include "./BSP/TIM/gtim.h"
#include "./BSP/ATK_MW8266D/atk_mw8266d.h"
#include "./BSP/STMFLASH/stmflash.h"
uint8_t  flag_tim_feeddog=0;
uint8_t  flag_feeddog=0;
uint8_t  flag_led=0;
uint16_t flag_AT=0;
uint8_t  flag_change;
uint8_t conunt_flag_tim_feeddog=0;
uint8_t  flag_other=0;//操作全部的与操作单路互斥。优化运行时间。



/* 要写入到STM32 FLASH的字符串数组 */
uint8_t Trigger_data[1];
#define TEXT_LENTH_data sizeof(Trigger_data) /* 数组长度 */
/*SIZE表示半字长(2字节), 大小必须是2的整数倍, 如果不是的话, 强制对齐到2的整数倍 */
#define SIZE TEXT_LENTH_data / 2 + ((TEXT_LENTH_data % 2) ? 1 : 0)
#define FLASH_ADDR 0X08008000 /* 设置FLASH 保存地址(必须为偶数，且其值要大于本代码所占用FLASH的大小 + 0X08000000)只要代码不超过32kb就不用改动 */






int main(void)
{
    
  HAL_Init();                                             /* 初始化HAL库 */
  sys_stm32_clock_init(RCC_PLL_MUL9);                     /* 设置时钟, 72Mhz */
	stmflash_read(FLASH_ADDR, (uint16_t *)Trigger_data, SIZE);  //读取flash的内容
	flag_change=Trigger_data[0];
	Trigger_init();
  delay_init(72);                                         /* 延时初始化 */   									
  usart_init(115200);                                     /* 初始化串口 */	
  led_init();                                             /* 初始化LED */
	delay_ms(500);																					//延时一会儿等待ESP8266连接上wifi
	LED0(0);
	delay_ms(500);
	LED0(1);
	
	atk_mw8266d_hw_init();
	atk_mw8266d_hw_reset();
	
	delay_ms(500);
	LED0(0);
	delay_ms(500);
	LED0(1);
	delay_ms(500);
	LED0(0);
	delay_ms(500);
	LED0(1);
	delay_ms(500);
	LED0(0);
	delay_ms(500);
	LED0(1);
	connect_atkcld();	
	gtim_timx_init(1000 - 1, 7200 - 1); //每100ms进入一次中断
	iwdg_init(IWDG_PRESCALER_64, 625); //1秒之内要喂狗
    while (1)
    {		
        if (g_usart_rx_sta & 0x8000)                        /* 接收到了数据? */
        {
        flag_change=Trigger_data[0];  
				flag_other=0;	 //收到信息了
/***************************************全部*************************************************/						
					if ((atk_mw8266d_check_act("turn_on_all"))==EQUAL)
						{
							
							flag_other=1;
							if(CHECK_1==1)
							{
							Trigger_TOGGLE_1();
							if (Read_Trigger_1)
							Trigger_data[0]=Trigger_data[0]|0x01;
							if (!Read_Trigger_1)
							Trigger_data[0]=Trigger_data[0]&0xfe;	
							}
							if(CHECK_2==1)
							{
							Trigger_TOGGLE_2();
							if (Read_Trigger_2)
							Trigger_data[0]=Trigger_data[0]|0x02;
							if (!Read_Trigger_2)
							Trigger_data[0]=Trigger_data[0]&0xfd;
							}
							if(CHECK_3==1)
							{
							Trigger_TOGGLE_3();
							if (Read_Trigger_3)
							Trigger_data[0]=Trigger_data[0]|0x04;
							if (!Read_Trigger_3)
							Trigger_data[0]=Trigger_data[0]&0xfb;
							}
							if(CHECK_4==1)
							{
							Trigger_TOGGLE_4();
							if (Read_Trigger_4)
							Trigger_data[0]=Trigger_data[0]|0x08;
							if (!Read_Trigger_4)
							Trigger_data[0]=Trigger_data[0]&0xf7;
							}
							
							
						}
						if ((atk_mw8266d_check_act("turn_off_all"))==EQUAL)
						{
							
							flag_other=1;
							if(CHECK_1==0)
							
							{
							Trigger_TOGGLE_1();
							if (Read_Trigger_1)
							Trigger_data[0]=Trigger_data[0]|0x01;
							if (!Read_Trigger_1)
							Trigger_data[0]=Trigger_data[0]&0xfe;
							}
							if(CHECK_2==0)
							
							{
							Trigger_TOGGLE_2();
							if (Read_Trigger_2)
							Trigger_data[0]=Trigger_data[0]|0x02;
							if (!Read_Trigger_2)
							Trigger_data[0]=Trigger_data[0]&0xfd;
							}
							if(CHECK_3==0)
							{
							Trigger_TOGGLE_3();
							if (Read_Trigger_3)
							Trigger_data[0]=Trigger_data[0]|0x04;
							if (!Read_Trigger_3)
							Trigger_data[0]=Trigger_data[0]&0xfb;
							}
							if(CHECK_4==0)
							{
							Trigger_TOGGLE_4();
							if (Read_Trigger_4)
							Trigger_data[0]=Trigger_data[0]|0x08;
							if (!Read_Trigger_4)
							Trigger_data[0]=Trigger_data[0]&0xf7;
							}
							
							
							
						}
						if ((atk_mw8266d_check_act("get_sta_all"))==EQUAL)
						{
							
							flag_other=1;
							
							if (CHECK_1)
							{atk_mw8266d_uart_printf("LIGHT_1_NOW_IS_OFF\r\n");}
							else
							{atk_mw8266d_uart_printf("LIGHT_1_NOW_IS_ON\r\n");}
							if (CHECK_2)
							{atk_mw8266d_uart_printf("LIGHT_2_NOW_IS_OFF\r\n");}
							else
							{atk_mw8266d_uart_printf("LIGHT_2_NOW_IS_ON\r\n");}
							if (CHECK_3)
							{atk_mw8266d_uart_printf("LIGHT_3_NOW_IS_OFF\r\n");}
							else
							{atk_mw8266d_uart_printf("LIGHT_3_NOW_IS_ON\r\n");}
							if (CHECK_4)
							{atk_mw8266d_uart_printf("LIGHT_4_NOW_IS_OFF\r\n");}
							else
							{atk_mw8266d_uart_printf("LIGHT_4_NOW_IS_ON\r\n");}
							
							
						}
						
						
						
						
						if (flag_other==0)
						{	
						/***************************************第一个*************************************************/	
						if ((atk_mw8266d_check_act("turn_on_1"))==EQUAL)
						{
							if(CHECK_1==1)
							{
							Trigger_TOGGLE_1();
							if (Read_Trigger_1)
							Trigger_data[0]=Trigger_data[0]|0x01;
							if (!Read_Trigger_1)
							Trigger_data[0]=Trigger_data[0]&0xfe;
							
							}
						}
						if ((atk_mw8266d_check_act("turn_off_1"))==EQUAL)
						{
							if(CHECK_1==0)
							
							{
							Trigger_TOGGLE_1();
							if (Read_Trigger_1)
							Trigger_data[0]=Trigger_data[0]|0x01;
							if (!Read_Trigger_1)
							Trigger_data[0]=Trigger_data[0]&0xfe;
							}
							
						}
						if ((atk_mw8266d_check_act("get_sta_1"))==EQUAL)
						{
							if (CHECK_1)
							{atk_mw8266d_uart_printf("LIGHT_1_NOW_IS_OFF\r\n");}
							else
							{atk_mw8266d_uart_printf("LIGHT_1_NOW_IS_ON\r\n");}
						
						}
						/***************************************第二个*************************************************/		

						
						if ((atk_mw8266d_check_act("turn_on_2"))==EQUAL)
						{
							if(CHECK_2==1)
							{
							Trigger_TOGGLE_2();
							if (Read_Trigger_2)
							Trigger_data[0]=Trigger_data[0]|0x02;
							if (!Read_Trigger_2)
							Trigger_data[0]=Trigger_data[0]&0xfd;
							}
						}
						if ((atk_mw8266d_check_act("turn_off_2"))==EQUAL)
						{
							
							if(CHECK_2==0)
							
							{
							Trigger_TOGGLE_2();
							if (Read_Trigger_2)
							Trigger_data[0]=Trigger_data[0]|0x02;
							if (!Read_Trigger_2)
							Trigger_data[0]=Trigger_data[0]&0xfd;
							}
							
						}
							
						
						if ((atk_mw8266d_check_act("get_sta_2"))==EQUAL)
						{
							if (CHECK_2)
							{atk_mw8266d_uart_printf("LIGHT_2_NOW_IS_OFF\r\n");}
							else
							{atk_mw8266d_uart_printf("LIGHT_2_NOW_IS_ON\r\n");}
						
						}	
						/*****************************************第三个***********************************************/
						
						if ((atk_mw8266d_check_act("turn_on_3"))==EQUAL)
						{
							if(CHECK_3==1)
							{
							Trigger_TOGGLE_3();
							if (Read_Trigger_3)
							Trigger_data[0]=Trigger_data[0]|0x04;
							if (!Read_Trigger_3)
							Trigger_data[0]=Trigger_data[0]&0xfb;
							}
						}
						if ((atk_mw8266d_check_act("turn_off_3"))==EQUAL)
						{
							if(CHECK_3==0)
							{
							Trigger_TOGGLE_3();
							if (Read_Trigger_3)
							Trigger_data[0]=Trigger_data[0]|0x04;
							if (!Read_Trigger_3)
							Trigger_data[0]=Trigger_data[0]&0xfb;
							}
							
						}
						if ((atk_mw8266d_check_act("get_sta_3"))==EQUAL)
						{
							if (CHECK_3)
							{atk_mw8266d_uart_printf("LIGHT_3_NOW_IS_OFF\r\n");}
							else
							{atk_mw8266d_uart_printf("LIGHT_3_NOW_IS_ON\r\n");}
						
						}	
						/*****************************************第四个***********************************************/
						if ((atk_mw8266d_check_act("turn_on_4"))==EQUAL)
						{
							if(CHECK_4==1)
							{
							Trigger_TOGGLE_4();
							if (Read_Trigger_4)
							Trigger_data[0]=Trigger_data[0]|0x08;
							if (!Read_Trigger_4)
							Trigger_data[0]=Trigger_data[0]&0xf7;
							}
						}
						if ((atk_mw8266d_check_act("turn_off_4"))==EQUAL)
						{
							if(CHECK_4==0)
							{
							Trigger_TOGGLE_4();
							if (Read_Trigger_4)
							Trigger_data[0]=Trigger_data[0]|0x08;
							if (!Read_Trigger_4)
							Trigger_data[0]=Trigger_data[0]&0xf7;
							}
							
						}
						if ((atk_mw8266d_check_act("get_sta_4"))==EQUAL)
						{
							if (CHECK_4)
							{atk_mw8266d_uart_printf("LIGHT_4_NOW_IS_OFF\r\n");}
							else
							{atk_mw8266d_uart_printf("LIGHT_4_NOW_IS_ON\r\n");}
						
						}	
					}
						
		if (flag_change!=Trigger_data[0])
		stmflash_write(FLASH_ADDR, (uint16_t *)Trigger_data, SIZE);		
		g_usart_rx_sta = 0;
		
		}

			if(flag_led>=5)//每500ms更新一下灯的状态
			{
				flag_led=0;
				if (CHECK_1)
					LED1(1);
				if (!CHECK_1)
					LED1(0);	

				if (CHECK_2)
					LED2(1);
				if (!CHECK_2)
					LED2(0);

				if (CHECK_3)
					LED3(1);
				if (!CHECK_3)
					LED3(0);
				if (CHECK_4)
					LED4(1);
				if (!CHECK_4)
					LED4(0);
				flag_led=0;
			}
			
			
			
					if (flag_feeddog>=5)
			{
				flag_feeddog=0;
				iwdg_feed();
				flag_feeddog=0;
			}
				
			
			if(flag_AT>=3000)//5分钟（3000）
			{
				flag_AT=0;
				flag_tim_feeddog=1;//此段有超过一秒的延时，要在中断中喂狗
				connect_atkcld();
				
				flag_tim_feeddog=0;//退出有延时的函数后，恢复正常的喂狗方式
				conunt_flag_tim_feeddog=0;
				flag_AT=0; //确保已经清零
				flag_tim_feeddog=0;
			}
			

		
	}	
}


