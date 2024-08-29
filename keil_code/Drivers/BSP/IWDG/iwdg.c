

#include "./BSP/IWDG/iwdg.h"


IWDG_HandleTypeDef iwdg_handle; /* �������Ź���� */

/**
 * @brief       ��ʼ���������Ź� 
 * @param       prer: IWDG_PRESCALER_4~IWDG_PRESCALER_256,��Ӧ4~256��Ƶ
 *   @arg       ��Ƶ���� = 4 * 2^prer. �����ֵֻ����256!
 * @param       rlr: �Զ���װ��ֵ,0~0XFFF. 
 * @note        ʱ�����(���):Tout=((4 * 2^prer) * rlr) / 40 (ms). 
 * @retval      ��
 */
void iwdg_init(uint8_t prer, uint16_t rlr)
{
    iwdg_handle.Instance = IWDG;
    iwdg_handle.Init.Prescaler = prer; /* ����IWDG��Ƶϵ�� */
    iwdg_handle.Init.Reload = rlr;     /* ��װ��ֵ */
    HAL_IWDG_Init(&iwdg_handle);       /* ��ʼ��IWDG��ʹ�� */
}

/**
 * @brief       ι�������Ź�
 * @param       ��
 * @retval      ��
 */
void iwdg_feed(void)
{
    HAL_IWDG_Refresh(&iwdg_handle);  /* ��װ�ؼ����� */
}
