

#include "./BSP/TIM/gtim.h"
#include "./BSP/IWDG/iwdg.h"
#include "./BSP/Trigger/Trigger.h"
#include "./BSP/LED/led.h"
extern uint8_t flag_feeddog;
extern uint8_t flag_led;
extern uint16_t flag_AT;
extern uint8_t conunt_flag_tim_feeddog;
extern uint8_t flag_tim_feeddog;

TIM_HandleTypeDef g_timx_handle;  /* 定时器x句柄 */

/**
 * @brief       通用定时器TIMX定时中断初始化函数
 * @note
 *              通用定时器的时钟来自APB1,当PPRE1 ≥ 2分频的时候
 *              通用定时器的时钟为APB1时钟的2倍, 而APB1为36M, 所以定时器时钟 = 72Mhz
 *              定时器溢出时间计算方法: Tout = ((arr + 1) * (psc + 1)) / Ft us.
 *              Ft=定时器工作频率,单位:Mhz
 *
 * @param       arr: 自动重装值。
 * @param       psc: 时钟预分频数
 * @retval      无
 */
void gtim_timx_init(uint16_t arr, uint16_t psc)
{
    GTIM_TIMX_INT_CLK_ENABLE();                                 /* 使能TIMx时钟 */

    g_timx_handle.Instance = GTIM_TIMX_INT;                     /* 通用定时器x */
    g_timx_handle.Init.Prescaler = psc;                         /* 预分频系数 */
    g_timx_handle.Init.CounterMode = TIM_COUNTERMODE_UP;        /* 递增计数模式 */
    g_timx_handle.Init.Period = arr;                            /* 自动装载值 */
    HAL_TIM_Base_Init(&g_timx_handle);

    HAL_NVIC_SetPriority(GTIM_TIMX_INT_IRQn, 1, 3);             /* 设置中断优先级，抢占优先级1，子优先级3 */
    HAL_NVIC_EnableIRQ(GTIM_TIMX_INT_IRQn);                     /* 开启ITMx中断 */

    HAL_TIM_Base_Start_IT(&g_timx_handle);                      /* 使能定时器x和定时器x更新中断 */
}

/**
 * @brief       定时器中断服务函数
 * @param       无
 * @retval      无
 */
void GTIM_TIMX_INT_IRQHandler(void)
{
    /* 以下代码没有使用定时器HAL库共用处理函数来处理，而是直接通过判断中断标志位的方式 */
    if(__HAL_TIM_GET_FLAG(&g_timx_handle, TIM_FLAG_UPDATE) != RESET)
    {
				flag_feeddog++;
				flag_led++;
				flag_AT++;
				if((flag_tim_feeddog==1)&(flag_feeddog==3))
				{
				flag_feeddog=0;
				conunt_flag_tim_feeddog++;
				iwdg_feed();
				if (conunt_flag_tim_feeddog>=200)
				{
					conunt_flag_tim_feeddog=0;
					flag_tim_feeddog=0;
				}
				flag_feeddog=0;
				}
        __HAL_TIM_CLEAR_IT(&g_timx_handle, TIM_IT_UPDATE);      /* 清除定时器溢出中断标志位 */
    }
}
