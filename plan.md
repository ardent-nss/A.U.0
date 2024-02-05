# Product Plan

* Raspberry Pi Pico-based
* Use of hardware:

  * Both UARTs
  * 2 additional pins for two LEDs (red, green)
  * USB serial terminal for basic traffic monitoring

## What will it do?

1. UART0 connected to "machine A"
2. UART1 connected to "machine B"
3. Core 0: copy data from UART0 RX -> UART1 TX
   1. Store data bits in uint8
   2. Calculate color from bits
   3. Display color in TX RGB LED
4. Core 1: copy data from UART1 RX -> UART0 TX
   1. Store data bits in uint8
   2. Calculate color from bits
   3. Display color in RX RGB LED 1
5. Provide data monitor on USB interface
