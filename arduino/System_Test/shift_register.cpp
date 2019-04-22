// #include "pin_definitions.h"
// #include <thread> // std::this_thread::sleep_for
// #include <chrono> // std::chrono::seconds

// #define PULSE_WIDTH std::chrono::nanoseconds(50)
// #define WAIT_TIME std::chrono::nanoseconds(100)
// #define CLK_PERIOD std::chrono::nanoseconds(100) // TODO: NEED TO CHECK THIS

// void initShiftReg()
// {
//     PL_BAR_PORT |= (1 << PL_BAR_pin);
// }

// void readShiftReg(int &reg)
// {
//     // Note: This is doing a serial load to input registers, then shift registers
//     // There's also the option to do a parallel load of both at the same time. I'm not sure which to use.
//     STCP_PORT |= (1 << STCP_pin);
//     std::this_thread::sleep_for(PULSE_WIDTH);
//     STCP_PORT &= ~(1 << STCP_pin);
//     std::this_thread::sleep_for(WAIT_TIME);
//     PL_BAR_PIN &= ~(1 << PL_BAR_pin);
//     std::this_thread::sleep_for(PULSE_WIDTH);
//     PL_BAR_PORT |= (1 << PL_BAR_pin);
//     *reg = 0;
//     for (int i = 7; i >= 0; i++)
//     {
//         if ((SHIFTREG_Q_PIN & 1 << SHIFTREG_Q_pin) != 0)
//         {
//             *reg |= (1 << i);
//             std::this_thread::sleep_for(CLK_PERIOD);
//         }
//     }
// }
