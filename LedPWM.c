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
#include "LedPWM.h"

void PwmInit(void)
{
	// Clock
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF); // 
	SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);
	SysCtlPWMClockSet(SYSCTL_PWMDIV_1);

	
	// Config
	
	GPIOPinConfigure(GPIO_PF1_M1PWM5);
	GPIOPinConfigure(GPIO_PF2_M1PWM6);
	GPIOPinConfigure(GPIO_PF3_M1PWM7);
	GPIOPinTypePWM(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 |	GPIO_PIN_3);
	
	// 
	
	PWMGenConfigure(PWM1_BASE, PWM_GEN_2, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);
	PWMGenConfigure(PWM1_BASE, PWM_GEN_3, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);
	
	// Period Set
	PWMGenPeriodSet(PWM1_BASE, PWM_GEN_2, 255);
	PWMGenPeriodSet(PWM1_BASE, PWM_GEN_3, 255);
	// Enable
	PWMGenEnable(PWM1_BASE, PWM_GEN_2);
	PWMGenEnable(PWM1_BASE, PWM_GEN_3);
	
	//Run
	PWMOutputState(PWM1_BASE, ( PWM_OUT_5_BIT | PWM_OUT_6_BIT | PWM_OUT_7_BIT ), true);
}
void PwmRunR(uint8_t Value)  // Run Red LGB 
{
		PWMPulseWidthSet(PWM1_BASE, PWM_OUT_5, Value);
		PWMOutputState(PWM1_BASE, PWM_OUT_5_BIT, true);
}	
void PwmRunG(uint8_t Value)
{
		PWMPulseWidthSet(PWM1_BASE, PWM_OUT_6, Value);
		PWMOutputState(PWM1_BASE, PWM_OUT_6_BIT , true);
}
void PwmRunB(uint8_t Value)
{
		PWMPulseWidthSet(PWM1_BASE, PWM_OUT_7, Value);
		PWMOutputState(PWM1_BASE,	PWM_OUT_7_BIT , true);
}
	


/* Example for decode
uint32_t RGB	=	0x0050A0Ff;
	uint8_t LR, LG,LB;
			LB = RGB & 0x0f;
			LG = (RGB >> 8) &0x0f;
			LR = (RGB >>16) %0x0f;
	

    while(1)
    {
			PwmRunR(LR);
			PwmRunB(LB);
			PwmRunG(LG);

			LR++;
			LG++;
			LB++;
			SysCtlDelay(500000);
		
		
		}
		*/
		
