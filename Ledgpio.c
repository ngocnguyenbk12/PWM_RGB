#include <stdint.h> 
#include <stdbool.h> 
#include "inc/hw_types.h" 
#include "inc/hw_gpio.h" 
#include "driverlib/pin_map.h" 
#include "driverlib/sysctl.c" 
#include "driverlib/sysctl.h" 
#include "driverlib/gpio.c" 
#include "driverlib/gpio.h" 

void SetInput(uint32_t ui32Port, uint8_t ui8Pin)
{
		SysCtlPeripheralEnable(ui32Port);
		GPIOPinTypeGPIOInput(ui32Port, ui8Pin);
		GPIOPadConfigSet(ui32Port, ui8Pin,GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPU);
}
void SetOutput(uint32_t ui32Port, uint8_t ui8Pin)
{
		SysCtlPeripheralEnable(ui32Port);
		GPIOPinTypeGPIOOutput(ui32Port, ui8Pin);
}

void GPIOToggle(uint32_t ui32Port, uint8_t ui8Pin)
{
		if( GPIOPinRead(ui32Port, ui8Pin) == ui8Pin	)
		{	
				GPIOPinWrite(ui32Port, ui8Pin, 0x00);
		}
		else 
		{
				GPIOPinWrite(ui32Port, ui8Pin, ui8Pin);
		}
}
	
void GPIOSet(uint32_t ui32Port, uint8_t ui8Pin)
{
		GPIOPinWrite(ui32Port, ui8Pin, ui8Pin);
}

void GPIOClear(uint32_t ui32Port, uint8_t ui8Pin)
{
		GPIOPinWrite(ui32Port, ui8Pin, 0x00);
}