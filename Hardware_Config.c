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

void Enable_All_Clocks(void);

uint32_t clockX;

void Hardware_Unit(void)  
{


    SysCtlMOSCConfigSet(SYSCTL_MOSC_HIGHFREQ);
	
    clockX = MAP_SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ |
                SYSCTL_OSC_MAIN | SYSCTL_USE_PLL |
                SYSCTL_CFG_VCO_480), 120000000);

    Enable_All_Clocks();
		
	
	  // USER LEDS FOR TIVA TM4C129 BOARD
    GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_1);
    GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, 0);
		GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_0);
    GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, 0);
	  GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_0);
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, 0);
		GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_4);
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4, 0);
														 
	
    SysTickPeriodSet(clockX/1000);

    SysTickIntEnable();

    SysTickEnable();

    IntPrioritySet(INT_SYSCTL,   0x00);
		
    IntMasterEnable();
		
}

void Parameters_Unit(void)
{

   


}

void GPIO_IN_OUT_Configs(void)
{
    GPIOPinTypeGPIOOutput(GPIO_PORTM_BASE, GPIO_PIN_7);     //status 3 led

    GPIOPinWrite(GPIO_PORTM_BASE, GPIO_PIN_7, !GPIO_PIN_7);

    GPIOPinTypeGPIOOutput(GPIO_PORTL_BASE, GPIO_PIN_1);     //status 2 led FOR GPS

    GPIOPinWrite(GPIO_PORTL_BASE, GPIO_PIN_1, !GPIO_PIN_1);


    GPIOPinTypeGPIOInput(GPIO_PORTL_BASE, GPIO_PIN_4);  // GPS PLL

}

void GPS_GPIO_Init(void)
{
    /**  GPS  EXTINT0  **/
    GPIOPinTypeGPIOOutput(GPIO_PORTM_BASE, GPIO_PIN_4);

    GPIOPinWrite(GPIO_PORTM_BASE, GPIO_PIN_4, !GPIO_PIN_4);

    /**  GPS  EXTINT1  **/
    GPIOPinTypeGPIOOutput(GPIO_PORTM_BASE, GPIO_PIN_2);

    GPIOPinWrite(GPIO_PORTM_BASE, GPIO_PIN_2, !GPIO_PIN_2);

    /**  GPS  RESET_N  **/
    GPIOPinTypeGPIOOutput(GPIO_PORTM_BASE, GPIO_PIN_1);

    GPIOPinWrite(GPIO_PORTM_BASE, GPIO_PIN_1, !GPIO_PIN_1);
}

void RS422_CH1_Uart4_Init(unsigned long baudrate)
{
    //SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOK);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART4);

    /** K GPIO_PIN_0 -> RX **/
    /** K GPIO_PIN_1 -> TX **/
    GPIOPinConfigure(GPIO_PK0_U4RX);
    GPIOPinTypeUART(GPIO_PORTK_BASE, GPIO_PIN_0);
    GPIOPinConfigure(GPIO_PK1_U4TX);
    GPIOPinTypeUART(GPIO_PORTK_BASE, GPIO_PIN_1);
    UARTConfigSetExpClk(UART4_BASE, clockX,baudrate,(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
    IntEnable(INT_UART4);
    UARTIntEnable(UART4_BASE, UART_INT_RX);
    UARTFIFODisable(UART4_BASE);

    /** K GPIO_PIN_2 -> RE **/
    /** K GPIO_PIN_3 -> DE **/
    GPIOPinTypeGPIOOutput(GPIO_PORTK_BASE, GPIO_PIN_2);
    GPIOPinTypeGPIOOutput(GPIO_PORTK_BASE, GPIO_PIN_3);
    GPIOPinWrite(GPIO_PORTK_BASE, GPIO_PIN_2, 0);
    GPIOPinWrite(GPIO_PORTK_BASE, GPIO_PIN_3, 0);

}

void RS422_CH3_Uart0_Init(unsigned long baudrate)
{
    //SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

    /** A GPIO_PIN_0 -> RX **/
    /** A GPIO_PIN_1 -> TX **/
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_1);
    UARTConfigSetExpClk(UART0_BASE, clockX, baudrate,(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
    IntEnable(INT_UART0);
    UARTIntEnable(UART0_BASE, UART_INT_RX);
    UARTFIFODisable(UART0_BASE);

    /** L GPIO_PIN_0 -> RE **/
    /** L GPIO_PIN_1 -> DE **/
    GPIOPinTypeGPIOOutput(GPIO_PORTL_BASE, GPIO_PIN_0);
    GPIOPinTypeGPIOOutput(GPIO_PORTL_BASE, GPIO_PIN_1);
    GPIOPinWrite(GPIO_PORTL_BASE, GPIO_PIN_0, 0);
    GPIOPinWrite(GPIO_PORTL_BASE, GPIO_PIN_1, 0);

}

void RS422_CH2_Uart6_Init(unsigned long baudrate)
{
    //SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOP);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART6);

    /** P GPIO_PIN_0 -> RX **/
    /** P GPIO_PIN_1 -> TX **/
    GPIOPinConfigure(GPIO_PP0_U6RX);
    GPIOPinTypeUART(GPIO_PORTP_BASE, GPIO_PIN_0);
    GPIOPinConfigure(GPIO_PP1_U6TX);
    GPIOPinTypeUART(GPIO_PORTP_BASE, GPIO_PIN_1);
    UARTConfigSetExpClk(UART6_BASE, clockX, baudrate,(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
    IntEnable(INT_UART6);
    UARTIntEnable(UART6_BASE, UART_INT_RX);
    UARTFIFODisable(UART6_BASE);

    /** M GPIO_PIN_5 -> RE **/
    /** M GPIO_PIN_6 -> DE **/
    GPIOPinTypeGPIOOutput(GPIO_PORTM_BASE, GPIO_PIN_5);
    GPIOPinTypeGPIOOutput(GPIO_PORTM_BASE, GPIO_PIN_6);
    GPIOPinWrite(GPIO_PORTM_BASE, GPIO_PIN_5, 0);
    GPIOPinWrite(GPIO_PORTM_BASE, GPIO_PIN_6, 0);

}

void RS422_CH4_Uart7_Init(unsigned long baudrate)
{
    //SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART7);

    /** C GPIO_PIN_4 -> RX **/
    /** C GPIO_PIN_5 -> TX **/
    GPIOPinConfigure(GPIO_PC4_U7RX);
    GPIOPinTypeUART(GPIO_PORTC_BASE, GPIO_PIN_4);
    GPIOPinConfigure(GPIO_PC5_U7TX);
    GPIOPinTypeUART(GPIO_PORTC_BASE, GPIO_PIN_5);
    UARTConfigSetExpClk(UART7_BASE, clockX, baudrate,(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
    IntEnable(INT_UART7);
    UARTIntEnable(UART7_BASE, UART_INT_RX);
    UARTFIFODisable(UART7_BASE);

    /** E GPIO_PIN_0 -> RE **/
    /** E GPIO_PIN_1 -> DE **/
    GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_0);
    GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_1);
    GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_0, 0);
    GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_1, 0);

}

void GPS_Uart2_Init(int br)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART2);
    //SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    GPIOPinConfigure(GPIO_PA6_U2RX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_6);
    GPIOPinConfigure(GPIO_PA7_U2TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_7);
    UARTConfigSetExpClk(UART2_BASE, clockX, br,
                        (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
                                UART_CONFIG_PAR_NONE));
    IntEnable(INT_UART2);
    UARTIntEnable(UART2_BASE, UART_INT_RX);
    UARTFIFODisable(UART2_BASE);

    //GPIOPinTypeGPIOOutput(GPIO_PORTM_BASE, GPIO_PIN_3);
    //GPIOPinWrite(GPIO_PORTM_BASE, GPIO_PIN_3, 0);
}


void Timer0_Init(void)
{
    /** 1 sn  **/

    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);

    TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
    TimerLoadSet(TIMER0_BASE, TIMER_A, (clockX / 1)-1); //1 SN
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    IntEnable(INT_TIMER0A);
    TimerEnable(TIMER0_BASE, TIMER_A);

    IntPrioritySet(INT_TIMER0A, 0x20);
}


void ETHERNET_INIT(void)
{



}

void Enable_All_Clocks(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOG);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOH);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOJ);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOK);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOL);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOM);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOP);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOQ);


}


void CAN_INIT(int fr)
{
    
}





