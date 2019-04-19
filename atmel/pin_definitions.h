#ifndef PINDEFS_H
#define PINDEFS_H

/* INTERFACING WITH PINS
 * 
  * PORT_X is used for output. PIN_X is used for input.
   * 
    * Write to high port using: DC_PORT |= 1 << DC_pin;    // Set DC pin high.
     * Write to low to port using: DC_PORT &= ~(1 << DC_pin); // Set DC pin low.
      * Read digital value from pin: DC_value = (DC_PIN & 1 << DC_pin) != 0; // Read DC pin.
       * 
       */

       #define ROTA_PORT PORTC
       #define ROTA_PIN PINC
       #define ROTA_pin 0
       #define ROTB_PORT PORTC
       #define ROTB_PIN PINC
       #define ROTB_pin 1
       #define FPS_RX_PORT PORTC
       #define FPS_RX_PIN PINC
       #define FPS_RX_pin 2
       #define FPS_TX_PORT PORTC
       #define FPS_TX_PIN PINC
       #define FPS_TX_pin 3
       #define MD1_SPI_PORT PORTC
       #define MD1_SPI_PIN PINC
       #define MD1_SPI_pin 4
       #define BUZZ_PORT PORTC
       #define BUZZ_PIN PINC
       #define BUZZ_pin 5

       #define MD2_SPI_PORT PORTD
       #define MD2_SPI_PIN PIND
       #define MD2_SPI_pin 0
       #define PL_BAR_PORT PORTD
       #define PL_BAR_PIN PIND
       #define PL_BAR_pin 1
       #define SOLENOID_FORWARD_PORT PORTD
       #define SOLENOID_FORWARD_PIN PIND
       #define SOLENOID_FORWARD_pin 2
       #define SOLENOID_REVERSE_PORT PORTD
       #define SOLENOID_REVERSE_PIN PIND
       #define SOLENOID_REVERSE_pin 3
       #define DC_PORT PORTD
       #define DC_PIN PIND
       #define DC_pin 4
       #define MD3_SPI_PORT PORTD
       #define MD3_SPI_PIN PIND
       #define MD3_SPI_pin 5
       #define SHIFTREG_Q_PORT PORTD
       #define SHIFTREG_Q_PIN PIND
       #define SHIFTREG_Q_pin 6
       #define ROT_SWITCH_PORT PORTD
       #define ROT_SWITCH_PIN PIND
       #define ROT_SWITCH_pin 7

       #define MD_ENABLE_PORT PORTB
       #define MD_ENABLE_PIN PINB
       #define MD_ENABLE_pin 0
       #define SD_SPI_PORT PORTB
       #define SD_SPI_PIN PINB
       #define SD_SPI_pin 1
       #define LCD_SPI_PORT PORTB
       #define LCD_SPI_PIN PINB
       #define LCD_SPI_pin 2
       #define MOSI_PORT PORTB
       #define MOSI_PIN PINB
       #define MOSI_pin 3
       #define MISO_PORT PORTB
       #define MISO_PIN PINB
       #define MISO_pin 4
       #define SCK_PORT PORTB
       #define SCK_PIN PINB
       #define SCK_pin 5
       #define SHCP_PORT PORTB
       #define SHCP_PIN PINB
       #define SHCP_pin 6
       #define STCP_PORT PORTB
       #define STCP_PIN PINB
       #define STCP_pin 7

       #endif

