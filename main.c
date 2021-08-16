#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_ints.h"
#include "inc/hw_timer.h"
#include "inc/hw_types.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/debug.h"
#include "driverlib/interrupt.h"
#include "driverlib/timer.h"
#include "driverlib/uart.h"
#include "driverlib/pin_map.h"
#include "driverlib/pwm.h"
#include "driverlib/gpio.c" 
#include "driverlib/sysctl.h" 
#include "inc/hw_gpio.h" 


//#include "FreeRTOS.h"
//#include "task.h"
// #include "Ledgpio.h"
#include "LedPWM.h"

#define Red GPIO_PIN_1 
#define Blue GPIO_PIN_2
#define Green GPIO_PIN_3
#define Led_Base GPIO_PORTF_BASE


// UART- TIMER CONFIG


void Timer0IntHandler(void);
void UartInit(void);
void Uart0IntHandler(void);
void Timer0Init(void);

// FREERTOS SETTING

//static void LEDGreenTask(void *pvParameters);
//static void LEDBlueTask(void *pvParameters);


int 	main(void)
{
		
		SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);  //40MHz = 400/2/5 = 40HMZ;;;;
//		UartInit();
//		Timer0Init();

		

//		xTaskCreate( LEDGreenTask, "LEDTask 1", configMINIMAL_STACK_SIZE, NULL,1, NULL );
//    xTaskCreate( LEDBlueTask,   "LEDTask 2", configMINIMAL_STACK_SIZE, NULL, 2, NULL );
//		vTaskStartScheduler();
	
		SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
		GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_3|GPIO_PIN_1);
		
	while(1)
	{
		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3|GPIO_PIN_1 , 0xff);
		SysCtlDelay(5000);
		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0x00);
		SysCtlDelay(5000);
		
	
	}
}

void Timer0IntHandler(void)
{
	TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
	if(GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_3))
	{
		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2| GPIO_PIN_3,0X06);
	}
	else
	{
		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2| GPIO_PIN_3,0X08);
	}
}
	

void Timer0Init(void)
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
		TimerConfigure(TIMER0_BASE, TIMER_CFG_A_PERIODIC_UP); 
		TimerLoadSet(TIMER0_BASE, TIMER_A, (SysCtlClockGet()/1)/2);
		IntEnable(INT_TIMER0A);
		TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
		IntMasterEnable();
		TimerEnable(TIMER0_BASE, TIMER_A);
		TimerDisable(TIMER0_BASE, TIMER_A);
	
}
void UartInit(void)
{
	// Init UART0 Pheripheral
	
	SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	
	// Configuration UART0 
	GPIOPinConfigure(GPIO_PA0_U0RX);
  GPIOPinConfigure(GPIO_PA1_U0TX);
	GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0|GPIO_PIN_1);
	UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200,(UART_CONFIG_WLEN_8| UART_CONFIG_STOP_ONE|UART_CONFIG_PAR_NONE));
	//     UART0 - Clock- Bautrate - 8 Bit data - 1 bit stop - 1 bit parity checking
	//
	
	// Interupt Enable
	// Interupt Enable Master
	IntMasterEnable();
	IntEnable(INT_UART0);
	UARTIntEnable(UART0_BASE,UART_INT_TX| UART_INT_RX);
	
	
	// Disable Uart Interupt
	IntDisable(INT_UART0);
	UARTIntDisable(UART0_BASE, UART_INT_TX| UART_INT_RX);
}

void Uart0IntHandler(void)
{
	unsigned long Status;
	Status = UARTIntStatus(UART0_BASE, true);
	UARTIntClear(UART0_BASE, Status);
	
	while(UARTCharsAvail(UART0_BASE))
	{
		for(int i=0; i<10;i++)
		{
		}
	}
	
}

/* static void LEDGreenTask(void *pvParameters)
{
    while (1)
    {
                GPIOSet1(Led_Base, Green);
								SysCtlDelay(1000000);
								GPIOClear1(Led_Base, Green);
			SysCtlDelay(1000000);
    }
}

//static void LEDBlueTask(void *pvParameters)
{

    while (1)
    {
                GPIOClear1(Led_Base, Blue);
			//         vTaskDelay(1000);
               SysCtlDelay(1000000);
    //         vTaskDelay(1000);
			GPIOSet1(Led_Base, Blue);
			SysCtlDelay(1000000);
    }
}


	
	

*/




