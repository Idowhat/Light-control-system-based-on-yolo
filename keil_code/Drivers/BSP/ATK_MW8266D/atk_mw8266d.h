/**
 ****************************************************************************************************
 * @file        atk_mw8266d.h
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2022-06-21
 * @brief       ATK-MW8266D模块驱动代码
 * @license     Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ****************************************************************************************************
 * @attention
 *
 * 实验平台:正点原子 MiniSTM32 V4开发板
 * 在线视频:www.yuanzige.com
 * 技术论坛:www.openedv.com
 * 公司网址:www.alientek.com
 * 购买地址:openedv.taobao.com
 *
 ****************************************************************************************************
 */

#ifndef __ATK_MW8266D_H
#define __ATK_MW8266D_H

#include "./SYSTEM/sys/sys.h"
#include "./BSP/ATK_MW8266D/atk_mw8266d_uart.h"




//引脚定义 
#define ATK_MW8266D_RST_GPIO_PORT           GPIOB
#define ATK_MW8266D_RST_GPIO_PIN            GPIO_PIN_4
#define ATK_MW8266D_RST_GPIO_CLK_ENABLE()   do{ __HAL_RCC_GPIOB_CLK_ENABLE(); }while(0) // PC口时钟使能 

//IO操作 
#define ATK_MW8266D_RST(x)                  do{ x ?                                                                                     \
                                                HAL_GPIO_WritePin(ATK_MW8266D_RST_GPIO_PORT, ATK_MW8266D_RST_GPIO_PIN, GPIO_PIN_SET) :  \
                                                HAL_GPIO_WritePin(ATK_MW8266D_RST_GPIO_PORT, ATK_MW8266D_RST_GPIO_PIN, GPIO_PIN_RESET); \
                                            }while(0)

																						
																						
																					
																						
																						
																						
																						
/* 错误代码 */
#define ATK_MW8266D_EOK         0   /* 没有错误 */
#define ATK_MW8266D_ERROR       1   /* 通用错误 */
#define ATK_MW8266D_ETIMEOUT    2   /* 超时错误 */
#define ATK_MW8266D_EINVAL      3   /* 参数错误 */
#define EQUAL       						4   /* 字符串相等 */
#define UNEQUAL    							5   /* 字符不串相等 */
#define STA_NULL								6		/*初始的未知状态*/



/*  原子云设备ID  */
#define DEMO_ATKCLD_DEV_ID      "60904729578091277825"			//原子云设备编号
#define DEMO_ATKCLD_DEV_PWD     "12345678"									//原子云设备密码



/* 操作函数 */
void atk_mw8266d_hw_reset(void);                                            /* ATK-MW8266D硬件复位 */
void atk_mw8266d_hw_init(void);
uint8_t atk_mw8266d_send_at_cmd(char *cmd, char *ack, uint32_t timeout);    /* ATK-MW8266D发送AT指令 */
uint8_t atk_mw8266d_restore(void);                                          /* ATK-MW8266D恢复出厂设置 */
uint8_t atk_mw8266d_at_test(void);                                          /* ATK-MW8266D AT指令测试 */
uint8_t atk_mw8266d_set_mode(uint8_t mode);                                 /* 设置ATK-MW8266D工作模式 */
uint8_t atk_mw8266d_sw_reset(void);                                         /* ATK-MW8266D软件复位 */
uint8_t atk_mw8266d_ate_config(uint8_t cfg);                                /* ATK-MW8266D设置回显模式 */
uint8_t atk_mw8266d_join_ap(char *ssid, char *pwd);                         /* ATK-MW8266D连接WIFI */
uint8_t atk_mw8266d_get_ip(char *buf);                                      /* ATK-MW8266D获取IP地址 */
uint8_t atk_mw8266d_connect_tcp_server(char *server_ip, char *server_port); /* ATK-MW8266D连接TCP服务器 */
uint8_t atk_mw8266d_enter_unvarnished(void);                                /* ATK-MW8266D进入透传 */
void atk_mw8266d_exit_unvarnished(void);                                    /* ATK-MW8266D退出透传 */
uint8_t atk_mw8266d_connect_atkcld(char *id, char *pwd);                    /* ATK-MW8266D连接原子云服务器 */
uint8_t atk_mw8266d_disconnect_atkcld(void);                                /* ATK-MW8266D断开原子云服务器连接 */
uint8_t atk_mw8266d_check_act(char *ack);																		//ATK-MW8266D接收命令并核对命令内容
void atk_mw8266d_keep_connect(void);																					//保持原子云连接
void  connect_atkcld (void);																									//上电时连接原子云
uint8_t atk_mw8266d_send_disconnect(char *cmd, char *ack,char *error , uint32_t timeout);
#endif
