#include "bsp.h"
#include "stm32f0xx.h"
#define GPIOCEN		(1U<<19)
#define PIN9 		(1U<<9)
#define LED_PIN		PIN9

void led_on(void)
{
	/*Set PC9 high*/
	GPIOC->ODR |=LED_PIN;
}

void led_off(void)
{
	/*Set PC9 low*/
	GPIOC->ODR &= ~LED_PIN;

}

