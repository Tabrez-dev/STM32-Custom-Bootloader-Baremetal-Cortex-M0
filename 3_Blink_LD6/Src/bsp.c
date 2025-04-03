#include "bsp.h"
#include "stm32f0xx.h"
#define GPIOCEN		(1U<<19)
#define PIN7 		(1U<<7)
#define LED_PIN		PIN7

void led_on(void)
{
	/*Set PC7 high*/
	GPIOC->ODR |=LED_PIN;
}

void led_off(void)
{
	/*Set PC7 low*/
	GPIOC->ODR &= ~LED_PIN;

}
