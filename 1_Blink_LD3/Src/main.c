//1_Blink_LD3
#include <stdio.h>
#include<stdbool.h>
#include "stm32f0xx.h"

bool btn_state;

struct btl_common_apis
{
	void(*led_init)(void);
	void(*led_toggle)(uint32_t dly);
	void(*led_on)(void);
	void(*led_off)(void);
	void(*system_uart_init)(void);
	void(*button_init)(void);
	bool(*get_btn_state)(void);
	void(*timebase_init)(void);
	void(*delay)(uint32_t delay);
};

int main()
{
	struct btl_common_apis *common_apis=(struct btl_common_apis
*)0x0801F000;
	/*Initialise  debug UART*/
	common_apis->system_uart_init();
	/*initialise timebase*/
	common_apis->timebase_init();
	/*init led*/
	common_apis->led_init();
	/*Init push button*/
	common_apis->button_init();
	while(1){
		printf("LD3 is Blinking...........\n\r");
		common_apis->delay(1000);
		common_apis->led_on();
		common_apis->delay(1000);
		common_apis->led_off();

	}
}
void SystemInit(void) {

	 // Note: On STM32F072RBT6 (Cortex-M0), the VTOR register is not available.
	    // The vector table for the bootloader is mapped at the base of the flash address (0x08000000).
	    // Therefore, the bootloader's vector table is used to handle exceptions, and not the application vector table.
	    // Copying the vector table to SRAM had lead to a crash, so i did not do it here.


//    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
//    /* Copy vector table from Flash (0x08001000) to SRAM (0x20000000) */
//    uint32_t i;
//    uint32_t *vectorTable = (uint32_t*) 0x20000000;  // SRAM base
//    uint32_t *appVectorTable = (uint32_t*) 0x08008000; // New vector table location
//    for (i = 0; i < 48; i++) {  // STM32F0 has 48 interrupt vectors
//        vectorTable[i] = appVectorTable[i];
//    }
//    /* Remap SRAM to address 0x00000000 */
//    SYSCFG->CFGR1 = (SYSCFG->CFGR1 & ~SYSCFG_CFGR1_MEM_MODE) | (0x1);
//    //printf("SYSCFG_CFGR1: 0x%08lX\n", SYSCFG->CFGR1);

}
