/*
 * **    blink.c -    blink with 1s delay
 * */

#include <stdio.h>
#include <unistd.h>
#include <gpiod.h>
#include "LED.h"
#define GPIOCHIP        0
#define GPIOLINE        27


void led(void) {
        struct gpiod_chip *output_chip;
        struct gpiod_line *output_line;
        int line_value;

        /* open chip and get line */
        output_chip = gpiod_chip_open_by_number(GPIOCHIP);
        output_line = gpiod_chip_get_line(output_chip, GPIOLINE);

        /* config as output and set a description */
        gpiod_line_request_output(output_line, "blink",GPIOD_LINE_ACTIVE_STATE_HIGH);
        gpiod_line_set_value(output_line, 1);
        sleep(1);
        gpiod_line_set_value(output_line, 0);
      }
