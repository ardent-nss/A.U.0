/*** main.cpp *****************************************************************\
 * Contributors: HackerDaGreat57                                              *
 * Copyright: (c) 2024 Ardent. Licensed under the MIT License.                *
 * Description: Makes the Pico act as a UART passthrough device with basic    *
 *   traffic monitoring capabilities and LED indication of flowing traffic    *
\******************************************************************************/

#include <stdio.h>
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
  //sleep_ms(7000);
  printf("\n"); // have some common decency, folks.

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

  //gpio_put(LED_RX,1);

  int __unused attempted_baudrate_300 = uart_init(UART0_ID,300);
  printf("UART baudrate set to %d (target was 300)\n", attempted_baudrate_300);
  sleep_ms(20);
  int __unused attempted_baudrate_1200 = uart_init(UART0_ID,1200);
  printf("UART baudrate set to %d (target was 1200)\n", attempted_baudrate_1200);
  sleep_ms(20);
  int __unused attempted_baudrate_2400 = uart_init(UART0_ID,2400);
  printf("UART baudrate set to %d (target was 2400)\n", attempted_baudrate_2400);
  sleep_ms(20);
  int __unused attempted_baudrate_4800 = uart_init(UART0_ID,4800);
  printf("UART baudrate set to %d (target was 4800)\n", attempted_baudrate_4800);
  sleep_ms(20);
  int __unused attempted_baudrate_9600 = uart_init(UART0_ID,9600);
  printf("UART baudrate set to %d (target was 9600)\n", attempted_baudrate_9600);
  sleep_ms(20);
  int __unused attempted_baudrate_19200 = uart_init(UART0_ID,19200);
  printf("UART baudrate set to %d (target was 19200)\n", attempted_baudrate_19200);
  sleep_ms(20);
  int __unused attempted_baudrate_38400 = uart_init(UART0_ID,38400);
  printf("UART baudrate set to %d (target was 38400)\n", attempted_baudrate_38400);
  sleep_ms(20);
  int __unused attempted_baudrate_57600 = uart_init(UART0_ID,57600);
  printf("UART baudrate set to %d (target was 57600)\n", attempted_baudrate_57600);
  sleep_ms(20);
  int __unused attempted_baudrate_76800 = uart_init(UART0_ID,76800);
  printf("UART baudrate set to %d (target was 76800)\n", attempted_baudrate_76800);
  sleep_ms(20);
  int __unused attempted_baudrate_115200 = uart_init(UART0_ID,115200);
  printf("UART baudrate set to %d (target was 115200)\n", attempted_baudrate_115200);
  sleep_ms(20);
  int __unused attempted_baudrate_230400 = uart_init(UART0_ID,230400);
  printf("UART baudrate set to %d (target was 230400)\n", attempted_baudrate_230400);
  sleep_ms(20);
  int __unused attempted_baudrate_460800 = uart_init(UART0_ID,460800);
  printf("UART baudrate set to %d (target was 460800)\n", attempted_baudrate_460800);
  sleep_ms(20);
  int __unused attempted_baudrate_576000 = uart_init(UART0_ID,576000);
  printf("UART baudrate set to %d (target was 576000)\n", attempted_baudrate_576000);
  sleep_ms(20);
  int __unused attempted_baudrate_921600 = uart_init(UART0_ID,921600);
  printf("UART baudrate set to %d (target was 921600)\n", attempted_baudrate_921600);
  sleep_ms(20);
  int __unused attempted_baudrate_2000000 = uart_init(UART0_ID,2000000);
  printf("UART baudrate set to %d (target was 2000000)\n", attempted_baudrate_2000000);
  sleep_ms(20);
  int __unused attempted_baudrate_3000000 = uart_init(UART0_ID,3000000);
  printf("UART baudrate set to %d (target was 3000000)\n", attempted_baudrate_3000000);
  sleep_ms(20);

  return 0;
}
