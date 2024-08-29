#include "./BSP/Trigger/Trigger.h"


extern uint8_t Trigger_data[1];
void Trigger_init(void)
{
    GPIO_InitTypeDef gpio_init_struct;
    Trigger_GPIO_CLK_ENABLE();                                 
	CHECK_GPIO_CLK_ENABLE();
    gpio_init_struct.Pin = Trigger_GPIO_PIN_1|Trigger_GPIO_PIN_2|Trigger_GPIO_PIN_3|Trigger_GPIO_PIN_4;                   
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_OD;            /* 开漏输出 */
    gpio_init_struct.Pull = GPIO_NOPULL;                    
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;          
    HAL_GPIO_Init(Trigger_GPIO_PORT_1, &gpio_init_struct);       
	gpio_init_struct.Pin = CHECK_GPIO_PIN_1|CHECK_GPIO_PIN_2|CHECK_GPIO_PIN_3|CHECK_GPIO_PIN_4;                      
    gpio_init_struct.Mode = GPIO_MODE_INPUT;                    /* 输入 */
	gpio_init_struct.Pull = GPIO_NOPULL;                        /* 浮空输入 */
    HAL_GPIO_Init(CHECK_GPIO_PORT_1, &gpio_init_struct);
	if (Trigger_data[0] & 0x01)
		Trigger_1(1);
	else if  (!(Trigger_data[0] & 0x01))
		Trigger_1(0);
	if (Trigger_data[0] & 0x02)
		Trigger_2(1); 
	else if (!(Trigger_data[0] & 0x02))
		Trigger_2(0); 
		if (Trigger_data[0] & 0x04)
		Trigger_3(1); 
	else if (!(Trigger_data[0] & 0x04))
		Trigger_3(0);  
		if (Trigger_data[0] & 0x08)
		Trigger_4(1);  
	else if (!(Trigger_data[0] & 0x08))
		Trigger_4(0);
	
}



