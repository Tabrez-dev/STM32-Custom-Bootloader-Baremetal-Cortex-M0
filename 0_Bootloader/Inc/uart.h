#ifndef __UART_H__
#define __UART_H__

#include "stm32f0xx.h"

void system_uart_init(void);
#define SR_RXNE (1U<<5)
#endif
