/*************************************************************************
* ALI SAHBAZ
*
*
* MAIN program for S_TEK_GATEWAY
*
* Date          : 23.09.2020
* By            : Saykal Electronics & Software Ltd.
* e-mail        : info@saykal.com
*
*************************************************************************/

#ifndef __TM4C129_IT_H
#define __TM4C129_IT_H

#define BSP_TICKS_PER_SEC 100U

void SysTick_ISR(void);
void WIFI_UartIntHandler(void);
void GSM_UartIntHandler(void);
void RS422UartCHANNEL_1_IntHandler(void);
void RS422UartCHANNEL_2_IntHandler(void);
void RS422UartCHANNEL_3_IntHandler(void);
void RS422UartCHANNEL_4_IntHandler(void);
void lwIPHostTimerHandler(void);
void CANIntHandler(void);
void Timer0AIntHandler(void);
void Timer1AIntHandler(void);
void Timer2AIntHandler(void);
void GPS_UartIntHandler(void);

void BSP_delay(uint32_t ticks);

#endif

