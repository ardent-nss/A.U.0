/*** main.cpp *****************************************************************\
 * Contributors: HackerDaGreat57                                              *
 * Copyright: (c) 2024 Ardent. Licensed under the MIT License.                *
 * Description: Makes the Pico act as a UART passthrough device with basic    *
 *   traffic monitoring capabilities and LED indication of flowing traffic    *
\******************************************************************************/

#include <stdio.h>
#include <iostream>
#include <stdbool.h>

#include "pico/stdlib.h"
#include "pico/mutex.h"
#include "pico/multicore.h"

#include "pico/binary_info.h"
#include "hardware/gpio.h"
#include "hardware/uart.h"

#define FLAG_VALUE 1 // I have no idea why, but this is involved in multicore functionality.

#define BAUD_RATE 921600 // Just the default; may be changed to any supported baud rate: 300,1200,2400,4800,
                         // 9600,19200,38400,57600,76800,115200,230400,460800,576000,921600,2000000,3000000
#define UART0_ID uart0
#define UART0_TX 0
#define UART0_RX 1
#define UART1_ID uart1
#define UART1_TX 6
#define UART1_RX 7

#define LED_RX 14
#define LED_TX 15

// void core1() {
//   //printf(printmsg);
//   multicore_fifo_push_blocking(FLAG_VALUE);
//   uint32_t g = multicore_fifo_pop_blocking();
//   if (g != FLAG_VALUE) {
//     printf("\033[1;101mERR:\033[0m Something's wrong on core 1??\n");
//   } else {
//     printf("\033[1;105mSETUP:\033[0m Core 1 initialized.\n");
//   }

//   printf("\033[1;92mCPU1:\033[0m Hey there!\n");

//   uint64_t counter1 = 0;
//   while(true) {
//     gpio_put(LED_TX, 1);

//     printf("\033[1;92mCPU1:\033[0m Hello world! %lld\n", counter1);

//     counter1++;
//     gpio_put(LED_TX, 0);
//     //sleep_us(1);
//   }
// }

int main() {
  set_sys_clock_khz(250000, true); // need for speed, literally
  stdio_init_all();
  printf("\n\n"); // have some common decency, folks.

  gpio_set_function(UART0_RX, GPIO_FUNC_UART);
  gpio_set_function(UART0_TX, GPIO_FUNC_UART);
  int __unused actual_uart_baudrate = uart_init(UART0_ID,BAUD_RATE);

  // printf("\033[2J\n\n");
  // printf("\033[1;31mArdent 0\033[39m Bootloader ~ \033[35mvW.X.Y.Z\033[0m\n"
  //        "\033[2m(c) Ardent 2023. Released under the MIT License.\033[0m\n\n");

  // printf("\033[1;30;46mINIT:\033[0m UART baudrate set to \033[96m%d\033[0m (target was \033[36m921600\033[0m)\n", actual_uart_baudrate);
  bi_decl(bi_program_description("A.U.0 firmware"));
  bi_decl(bi_1pin_with_name(LED_RX, "RX status LED"));
  bi_decl(bi_1pin_with_name(LED_TX, "TX status LED"));

  gpio_init(LED_RX);
  gpio_init(LED_TX);
  gpio_set_dir(LED_RX, GPIO_OUT);
  gpio_set_dir(LED_TX, GPIO_OUT);

  for(uint8_t i = 1; i <= 10; i++) { // give the user 10 seconds to connect to the USB serial terminal. (This
    gpio_put(LED_RX,1);              // is because serial connection programs auto-disconnect when the device
    gpio_put(LED_TX,1);              // is removed, adding the need to reconnect manually every MCU power-on)
    sleep_ms(500);
    gpio_put(LED_RX,0);
    gpio_put(LED_TX,0);
    sleep_ms(500);
  }

  return 0;
}
