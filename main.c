/****************************************************************************************
* ALI SAHBAZ
*
*
* ASOS mini RTOS for TM4C129
*
* Date          : 12.05.2021
* By            : Ali Sahbaz
* e-mail        : ali_sahbaz@outlook.com
*/
#include "main.h"

 
static uint32_t stack_blinky1[40];

static os_thread_t blinky1;

static uint32_t stack_blinky2[40];

static os_thread_t blinky2;

static uint32_t stack_blinky3[40];

static os_thread_t blinky3;

static uint32_t stack_blinky4[40];

static os_thread_t blinky4;

static void main_blinky1() {
	
    while (1) 
		{
        GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, 0);
			
        BSP_delay(200);
			
        GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, GPIO_PIN_1);
			
        BSP_delay(200);
    }
}




static void main_blinky2() {
	
    while (1) 
		{
			  GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, 0);
			
        BSP_delay(200);
			
        GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, GPIO_PIN_0);
			
        BSP_delay(200);
    }
}




static void main_blinky3() {
	
    while (1) {
			
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4, 0);
			
        BSP_delay(1000);
			
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_PIN_4);
			
        BSP_delay(500);
			
    }
}




static void main_blinky4() {
	
    while (1) {
			
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, 0);
			
        BSP_delay(500);
			
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, GPIO_PIN_0);
			
        BSP_delay(500);
			
    }
}


int main(void)
{
	  Hardware_Unit();
	
		my_os_init();

    my_os_thread_start(&blinky1,
                       &main_blinky1,
                       stack_blinky1, 
											 100,
	                     sizeof(stack_blinky1));

    my_os_thread_start(&blinky2,
											 &main_blinky2,
											 stack_blinky2, 
											 1,
											 sizeof(stack_blinky2));
	
		my_os_thread_start(&blinky3,
											 &main_blinky3,
											 stack_blinky3, 
											 1,
											 sizeof(stack_blinky3));

		my_os_thread_start(&blinky4,
											 &main_blinky4,
											 stack_blinky4, 
											 1,
											 sizeof(stack_blinky4));
								
	  my_os_run();
}

