# Product Plan

* Raspberry Pi Pico-based
* Use of hardware:
  * Both UARTs
  * 6 additional pins for two RGB LEDs
  * 6 PWMs (for precise control over color in the LEDs)
  * USB serial terminal for basic traffic monitoring
* 7-switch DIP

## What will it do?

1. UART0 connected to "machine A"
2. UART1 connected to "machine B"
3. Baud rate set via first 4 switches in DIP
   1. Decimal representation of baud rates:
      1. 110
      2. 150
      3. 300
      4. 1200
      5. 2400
      6. 4800
      7. 9600
      8. 19200
      9. 38400
      10. 57600
      11. 76800
      12. 115200
      13. 230400
      14. 460800
      15. 576000
      16. 921600
4. Data bits set by 5th and 6th switches in DIP
   1. Decimal representation of data bits:
      1. 5
      2. 6
      3. 7
      4. 8
5. Stop bits set by 7th switch in DIP
   1. If off, 1 stop bit.
   2. If on, 2 stop bits.
6. Core 0: copy data from UART0 RX -> UART1 TX
   1. Store data bits in uint8
   2. Calculate color from bits
   3. Display color in TX RGB LED
7. Core 1: copy data from UART1 RX -> UART0 TX
   1. Store data bits in uint8
   2. Calculate color from bits
   3. Display color in RX RGB LED 1
8. Provide data monitor on USB interface
