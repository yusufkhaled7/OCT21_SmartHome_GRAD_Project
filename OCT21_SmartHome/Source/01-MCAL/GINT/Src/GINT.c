/********************************
 * GINT.c
 * Created on: Sep , 2022
 * Author: Mazen Mokbel
 *******************************/

#include "GINT_Reg.h"
#include "Bit_Math.h"

void GINT_vidEnableAllInterrupts(void)
{
	SET_BIT(GINT_SREG_REG,7);
}

void GINT_vidDisableAllInterrupts(void)
{
	CLEAR_BIT(GINT_SREG_REG,7);
}
