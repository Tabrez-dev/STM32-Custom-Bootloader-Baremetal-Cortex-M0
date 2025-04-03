#include "bsp.h"
#include "stm32f0xx.h"
#include "timebase.h"
#define GPIOAEN 	(1U<<17)
#define GPIOCEN		(1U<<19)
#define PIN6 		(1U<<6)
#define LED_PIN		PIN6
#define PIN0		(1U<<0)
#define BTN_PIN		PIN0

void led_init(void)
{
	/*Enable clock access to GPIOC*/
	RCC->AHBENR |= GPIOCEN;
	/*Set PC6->LD3 mode to output mode*/
	GPIOC->MODER |= (1U<<12);
	GPIOC->MODER &=~(1U<<13);

	RCC->AHBENR |= GPIOCEN;
	/*Set PC8->LD4 mode to output mode*/
	GPIOC->MODER |= (1U<<16);
	GPIOC->MODER &=~(1U<<17);

	RCC->AHBENR |= GPIOCEN;
	/*Set PC9->LD5 mode to output mode*/
	GPIOC->MODER |= (1U<<18);
	GPIOC->MODER &=~(1U<<19);

	RCC->AHBENR |= GPIOCEN;
	/*Set PC7->LD6 mode to output mode*/
	GPIOC->MODER |= (1U<<14);
	GPIOC->MODER &=~(1U<<15);
}

void led_toggle(uint32_t dly)
{
	/*Set PC6 high*/
	GPIOC->ODR ^=LED_PIN;
	delay(dly);
}

void led_on(void)
{
	/*Set PC6 high*/
	GPIOC->ODR |=LED_PIN;
}

void led_off(void)
{
	/*Set PC6 low*/
	GPIOC->ODR &= ~LED_PIN;

}

void button_init(void)
{
	/*Enable port access to PORTA*/
	RCC->AHBENR |= GPIOAEN;
	/*Set PA0 as input pin*/
	GPIOA->MODER &= ~(1U<<0);
	GPIOA->MODER &= ~(1U<<1);

}

bool get_btn_state(void)
{
	/*Check if button is pressed, not btn is  active high btn*/
	if(GPIOA->IDR & BTN_PIN){
		return true;
	}else{
		return false;
	}
}
