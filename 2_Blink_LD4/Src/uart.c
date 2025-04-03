#include  <stdint.h>
#include "uart.h"

#define SR_TXE				(1U<<7)
static void uart_write(int ch);
int __io_putchar(int ch)
{
	uart_write(ch);
	return ch;
}

static void uart_write(int ch)
{
	/*Make sure tx data reg is empty*/
	while(!(USART1->ISR & SR_TXE));
	/*Write to transmit data reg*/
	USART1->TDR = (ch & 0xFF);
}


