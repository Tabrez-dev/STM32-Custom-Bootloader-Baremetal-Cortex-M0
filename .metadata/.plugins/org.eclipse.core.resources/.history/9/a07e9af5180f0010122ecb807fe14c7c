#include "bsp.h"
#include "stm32f0xx.h"

#define GPIOCEN		(1U<<19)
#define PIN8 		(1U<<8)
#define LED_PIN		PIN8


void led_on(void)
{
	/*Set PC8 high*/
	GPIOC->ODR |=LED_PIN;
}

void led_off(void)
{
	/*Set PC8 low*/
	GPIOC->ODR &= ~LED_PIN;
}

