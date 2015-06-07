#include <diag/Trace.h>
#include <stm32f4xx_hal.h>
#include <stm32f4xx_hal_gpio.h>

#include "button.h"

extern "C" void EXTI1_IRQHandler(void);
extern "C" void EXTI3_IRQHandler(void);
extern "C" void EXTI9_5_IRQHandler(void);

Button button1(SW1_PIN);
Button button2(SW2_PIN);
Button button3(SW3_PIN);

Button *const buttons[] = {&button1, &button2, &button3};

Button::Button(const pin_t &button_pin)
	:pin(button_pin)
{
}

void Button::init(void)
{
	GPIO_InitTypeDef gpio;
	gpio.Pin = pin.number;
	gpio.Mode = GPIO_MODE_INPUT | GPIO_MODE_IT_RISING;
	gpio.Speed = GPIO_SPEED_HIGH;
	gpio.Pull = GPIO_NOPULL;
	gpio.Alternate = pin.af;

	HAL_GPIO_Init(pin.port, &gpio);
}

void Button::change_event(void)
{
	trace_printf("%p got button: %d\n", this, is_pressed());
}

extern "C"
void EXTI1_IRQHandler(void)
{
	button3.change_event();
	__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_1);
}

extern "C"
void EXTI3_IRQHandler(void)
{
	button1.change_event();
	__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_3);
}

extern "C"
void EXTI9_5_IRQHandler(void)
{
	button2.change_event();
	__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_5);
}

/*void HAL_GPIO_EXTI_Callback(uint16_t pin)
{
	if(pin & GPIO_PIN_3)
	if(pin & GPIO_PIN_5)
	if(pin & GPIO_PIN_1)
}
*/
