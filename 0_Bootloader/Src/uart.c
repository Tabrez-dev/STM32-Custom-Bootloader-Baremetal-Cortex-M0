#include  <stdint.h>
#include "uart.h"
#define GPIOAEN 	(1U<<17)
#define UART1EN 	(1U<<14)
#define DBG_UART_BAUDRATE 	115200
#define SYS_FREQ			8000000
#define APB2_CLK			SYS_FREQ
#define CR1_TE 				(1U<<3)
#define CR1_RE 				(1U<<2)
#define CR1_RXNEIE 			(1U<<5)
#define CR1_UE 				(1U<<0)
#define SR_TXE				(1U<<7)
static void uart_set_baud_rate(uint32_t periph_clk,uint32_t baudrate);
static void uart_write(int ch);
static uint16_t compute_uart_bd(uint32_t periph_clk,uint32_t baudrate);
int __io_putchar(int ch)
{
	uart_write(ch);
	return ch;
}

void system_uart_init(void){
	/*Enable clock access to GPIOA*/
	RCC->AHBENR |= GPIOAEN;
	/*Set the mode of PA9 and PA10 to AF mode*/
	GPIOA->MODER &= ~(1U<<18);
	GPIOA->MODER |= (1U<<19);
	//PA10 RX
	GPIOA->MODER &= ~(1U<<20);
	GPIOA->MODER |= (1U<<21);
	/*Set AF type to AF1(USART1_TX/RX)*/
	GPIOA->AFR[1] |= (1U<<4);
	GPIOA->AFR[1] &= ~(1U<<5);
	GPIOA->AFR[1] &= ~(1U<<6);
	GPIOA->AFR[1] &= ~(1U<<7);

	GPIOA->AFR[1] |= (1U<<8);
	GPIOA->AFR[1] &= ~(1U<<9);
	GPIOA->AFR[1] &= ~(1U<<10);
	GPIOA->AFR[1] &= ~(1U<<11);

	/*Enable clock access to USART1*/
	RCC->APB2ENR |= UART1EN;
	/*Configure uart baud rate*/
	uart_set_baud_rate(APB2_CLK,DBG_UART_BAUDRATE);
	/*Configure transfer direction*/
	USART1->CR1 = CR1_TE | CR1_RE;
	/*Enable RXNE interrupt*/
	USART1->CR1 |= CR1_RXNEIE;
     // Enable USART1 interrupt

	/*Enable UART module*/
	USART1->CR1 |= CR1_UE;//just update value of bit 0

	/*Enable uart1 interrupt in nvic*/
	NVIC_EnableIRQ(USART1_IRQn);

}

static void uart_write(int ch)
{
	/*Make sure tx data reg is empty*/
	while(!(USART1->ISR & SR_TXE));
	/*Write to transmit data reg*/
	USART1->TDR = (ch & 0xFF);
}

static uint16_t compute_uart_bd(uint32_t periph_clk,uint32_t baudrate)
{
	return ((periph_clk + (baudrate/2U))/baudrate);//round off technineuq
}

static void uart_set_baud_rate(uint32_t periph_clk,uint32_t baudrate)
{
	USART1->BRR = compute_uart_bd(periph_clk,baudrate);
}


