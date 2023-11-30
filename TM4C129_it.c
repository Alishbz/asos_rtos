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


static uint32_t volatile l_tickCtr;

void sysTick_Handler(void)
{
		++l_tickCtr; 					// Systick Delay Counter

		__disable_irq();
		my_os_scheduleing();  // My Operating System Time & Order synchronization
		__enable_irq();
	
}

void WIFI_UartIntHandler(void)
{

}

void GSM_UartIntHandler(void)
{

}



void RS422UartCHANNEL_1_IntHandler(void)
{
    

}

void RS422UartCHANNEL_2_IntHandler(void)
{
   
}

void RS422UartCHANNEL_3_IntHandler(void)
{
   
}



void RS422UartCHANNEL_4_IntHandler(void)
{
    
}


void GPS_UartIntHandler(void)
{
   
}


void lwIPHostTimerHandler(void)
{

}


void CANIntHandler(void) {

   
}


void Timer0AIntHandler(void)//1sn
{

   
}

void Timer1AIntHandler(void)
{

}

void Timer2AIntHandler(void)
{

}


/***************  DELAY UNIT  ****************/

uint32_t BSP_tickCtr(void) {
    uint32_t tickCtr;

    __disable_irq();
    tickCtr = l_tickCtr;
    __enable_irq();

    return tickCtr;
}

void BSP_delay(uint32_t ticks) {
    uint32_t start = BSP_tickCtr();
    while ((BSP_tickCtr() - start) < ticks) {
    }
}

