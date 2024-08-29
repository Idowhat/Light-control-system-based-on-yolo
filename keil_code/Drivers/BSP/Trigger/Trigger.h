#ifndef _Trigger_H
#define _Trigger_H
#include "./SYSTEM/sys/sys.h"


/******************************************************************************************/
/* 引脚 定义 */

#define Trigger_GPIO_PORT_1                  GPIOB
#define Trigger_GPIO_PIN_1                   GPIO_PIN_15
#define Trigger_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOB_CLK_ENABLE(); }while(0)             /* PB口时钟使能 */
#define Trigger_GPIO_PORT_2                  GPIOB
#define Trigger_GPIO_PIN_2                   GPIO_PIN_14
#define Trigger_GPIO_PORT_3                     GPIOB
#define Trigger_GPIO_PIN_3                   GPIO_PIN_13
#define Trigger_GPIO_PORT_4                  GPIOB
#define Trigger_GPIO_PIN_4                   GPIO_PIN_12


#define Read_Trigger_1 HAL_GPIO_ReadPin(Trigger_GPIO_PORT_1, Trigger_GPIO_PIN_1)
#define Read_Trigger_2 HAL_GPIO_ReadPin(Trigger_GPIO_PORT_2, Trigger_GPIO_PIN_2)
#define Read_Trigger_3 HAL_GPIO_ReadPin(Trigger_GPIO_PORT_3, Trigger_GPIO_PIN_3)
#define Read_Trigger_4 HAL_GPIO_ReadPin(Trigger_GPIO_PORT_4, Trigger_GPIO_PIN_4)

#define CHECK_GPIO_PORT_1                  GPIOB
#define CHECK_GPIO_PIN_1                  GPIO_PIN_8
#define CHECK_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOB_CLK_ENABLE(); }while(0) 
#define CHECK_GPIO_PORT_2                  GPIOB
#define CHECK_GPIO_PIN_2                  GPIO_PIN_9 
#define CHECK_GPIO_PORT_3                  GPIOB
#define CHECK_GPIO_PIN_3                  GPIO_PIN_10
#define CHECK_GPIO_PORT_4                  GPIOB
#define CHECK_GPIO_PIN_4                  GPIO_PIN_11
#define CHECK_1        HAL_GPIO_ReadPin(CHECK_GPIO_PORT_1, CHECK_GPIO_PIN_1)
#define CHECK_2        HAL_GPIO_ReadPin(CHECK_GPIO_PORT_2, CHECK_GPIO_PIN_2)
#define CHECK_3        HAL_GPIO_ReadPin(CHECK_GPIO_PORT_3, CHECK_GPIO_PIN_3)
#define CHECK_4        HAL_GPIO_ReadPin(CHECK_GPIO_PORT_4, CHECK_GPIO_PIN_4)
/******************************************************************************************/
/* 继电器端口定义 */
#define Trigger_1(x)   do{ x ? \
                      HAL_GPIO_WritePin(Trigger_GPIO_PORT_1, Trigger_GPIO_PIN_1, GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(Trigger_GPIO_PORT_1, Trigger_GPIO_PIN_1, GPIO_PIN_RESET); \
                  }while(0) 

									
									
#define Trigger_2(x)   do{ x ? \
                      HAL_GPIO_WritePin(Trigger_GPIO_PORT_2, Trigger_GPIO_PIN_2, GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(Trigger_GPIO_PORT_2, Trigger_GPIO_PIN_2, GPIO_PIN_RESET); \
                  }while(0) 

									
									
#define Trigger_3(x)   do{ x ? \
                      HAL_GPIO_WritePin(Trigger_GPIO_PORT_3, Trigger_GPIO_PIN_3, GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(Trigger_GPIO_PORT_3, Trigger_GPIO_PIN_3, GPIO_PIN_RESET); \
                  }while(0) 

									
									
#define Trigger_4(x)   do{ x ? \
                      HAL_GPIO_WritePin(Trigger_GPIO_PORT_4, Trigger_GPIO_PIN_4, GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(Trigger_GPIO_PORT_4, Trigger_GPIO_PIN_4, GPIO_PIN_RESET); \
                  }while(0) 

									
									
									
									
									
									
									
									

/* 继电器取反定义 */
#define Trigger_TOGGLE_1()   do{ HAL_GPIO_TogglePin(Trigger_GPIO_PORT_1, Trigger_GPIO_PIN_1); }while(0) 

#define Trigger_TOGGLE_2()   do{ HAL_GPIO_TogglePin(Trigger_GPIO_PORT_2, Trigger_GPIO_PIN_2); }while(0)

#define Trigger_TOGGLE_3()   do{ HAL_GPIO_TogglePin(Trigger_GPIO_PORT_3, Trigger_GPIO_PIN_3); }while(0)

#define Trigger_TOGGLE_4()   do{ HAL_GPIO_TogglePin(Trigger_GPIO_PORT_4, Trigger_GPIO_PIN_4); }while(0)



/* 翻转继电器 */     
/******************************************************************************************/
/* 外部接口函数*/
void Trigger_init(void);                                                                            /* 初始化 */
#endif
