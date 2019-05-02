#include "pin_definitions.h"
#include <util/delay.h>

#define PULSE_WIDTH 20
#define WAIT_TIME 20
#define SETTLE_TIME 10
#define CLK_PERIOD 50 // TODO: This should be the clock period of SHCP.

void initShiftReg()
{
    PL_BAR_PORT |= (1 << PL_BAR_pin);
}

void readShiftReg(int &reg)
{
    // Note: This is doing a serial load to input registers, then shift registers
    // There's also the option to do a parallel load of both at the same time. I'm not sure which to use.
    STCP_PORT |= (1 << STCP_pin);
    _delay_us(PULSE_WIDTH);
    STCP_PORT &= ~(1 << STCP_pin);
    _delay_us(WAIT_TIME);
    PL_BAR_PIN &= ~(1 << PL_BAR_pin);
    _delay_us(PULSE_WIDTH);
    PL_BAR_PORT |= (1 << PL_BAR_pin);
    reg = 0;
    for (int i = 7; i >= 0; i++)
    {
        SHCP_PORT |= (1 << SHCP_pin);
        _delay_us(SETTLE_TIME);
        if ((SHIFTREG_Q_PIN & 1 << SHIFTREG_Q_pin) != 0)
        {
            reg |= (1 << i);
        }
        SHCP_PORT &= ~(1 << SHCP_pin);
        _delay_us(SETTLE_TIME);
    }
}
