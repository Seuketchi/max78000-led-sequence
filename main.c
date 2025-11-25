/******************************************************************************
 * MAX78000 LED Demo - 3x3 LED Matrix Version
 ******************************************************************************/

/***** Includes *****/
#include <stdio.h>
#include <stdint.h>
#include "mxc_device.h"
#include "board.h"
#include "mxc_delay.h"
#include "gpio.h"

/***** Definitions *****/

// 3×3 matrix → 9 LEDs
#define NUM_LEDS 9
#define BUTTON_PORT MXC_GPIO1
#define BUTTON_PIN  MXC_GPIO_PIN_7

typedef struct {
    mxc_gpio_regs_t *port;
    uint32_t pin;
} led_pin_t;

int mode = 0;  // 0 = heartbeat, 1 = snake


/**
 * LED layout (3×3):
 *
 *  [0] [1] [2]
 *  [3] [4] [5]
 *  [6] [7] [8]
 */

// Pin mapping (you provided)
const led_pin_t leds[NUM_LEDS] = {
    {MXC_GPIO0, MXC_GPIO_PIN_17}, // LED 0 - top row
    {MXC_GPIO0, MXC_GPIO_PIN_16}, // LED 1
    {MXC_GPIO3, MXC_GPIO_PIN_1},  // LED 2

    {MXC_GPIO0, MXC_GPIO_PIN_19}, // LED 3 - middle row
    {MXC_GPIO0, MXC_GPIO_PIN_11}, // LED 4
    {MXC_GPIO0, MXC_GPIO_PIN_8},  // LED 5

    {MXC_GPIO1, MXC_GPIO_PIN_1},  // LED 7
    {MXC_GPIO2, MXC_GPIO_PIN_4},   // LED 8
    {MXC_GPIO2, MXC_GPIO_PIN_3},  // LED 6 - bottom row

};

/***** Basic Button Helpers *****/
void button_init(void)
{
    gpio_init_input(BUTTON_PORT, BUTTON_PIN);
}

int button_pressed(void)
{
    if (gpio_read(BUTTON_PORT, BUTTON_PIN) == LOW) {
        MXC_Delay(MXC_DELAY_MSEC(20));  // debounce
        if (gpio_read(BUTTON_PORT, BUTTON_PIN) == LOW)
            return 1;
    }
    return 0;
}

/***** Basic LED Helpers *****/

void led_init(void)
{
    for (int i = 0; i < NUM_LEDS; i++) {
        gpio_init_output(leds[i].port, leds[i].pin);
        gpio_clear(leds[i].port, leds[i].pin);
    }
}

void led_on(int i) {
    if (i >= 0 && i < NUM_LEDS) gpio_set(leds[i].port, leds[i].pin);
}

void led_off(int i) {
    if (i >= 0 && i < NUM_LEDS) gpio_clear(leds[i].port, leds[i].pin);
}

void led_toggle(int i) {
    if (i >= 0 && i < NUM_LEDS) gpio_toggle(leds[i].port, leds[i].pin);
}

void all_leds_off(void) {
    for (int i = 0; i < NUM_LEDS; i++) gpio_clear(leds[i].port, leds[i].pin);
}

void all_leds_on(void) {
    for (int i = 0; i < NUM_LEDS; i++) gpio_set(leds[i].port, leds[i].pin);
}

void fade_led(int led, int fade_in)
{
    // fade_in = 1 → fade-in
    // fade_in = 0 → fade-out

    for (int level = 0; level < 100; level++) {
        int duty = fade_in ? level : (100 - level);

        // Software PWM cycle
        for (int t = 0; t < 100; t++) {
            if (t < duty)
                gpio_set(leds[led].port, leds[led].pin);
            else
                gpio_clear(leds[led].port, leds[led].pin);
            
            // small delay for PWM speed
            MXC_Delay(MXC_DELAY_USEC(50));
        }
    }
}


/***** Patterns (still using heartbeat & snake) *****/

void heartbeat_pattern(void)
{
    all_leds_on();
    MXC_Delay(MXC_DELAY_MSEC(100));
    all_leds_off();
    MXC_Delay(MXC_DELAY_MSEC(100));

    all_leds_on();
    MXC_Delay(MXC_DELAY_MSEC(100));
    all_leds_off();

    MXC_Delay(MXC_DELAY_MSEC(600));
}

void snake_pattern(void)
{
    // 3x3 snake path (L→R, R→L, top→bottom)
    int snake_path[NUM_LEDS] = {
        0, 1, 2,   // top row
        5, 4, 3,   // middle row (reverse)
        6, 7, 8    // bottom row
    };

    all_leds_off();

    for (int i = 0; i < NUM_LEDS; i++) {

        // Turn on head of the snake
        led_on(snake_path[i]);

        // If not the first LED, turn on the trailing LED
        if (i > 0) {
            led_on(snake_path[i - 1]);
        }

        MXC_Delay(MXC_DELAY_MSEC(150));

        // Turn off both lights before next step
        if (i > 0) led_off(snake_path[i - 1]);
        led_off(snake_path[i]);
    }

    MXC_Delay(MXC_DELAY_MSEC(200));
}



/******************************************************************************/

int main(void)
{
    int count = 0;

    printf("\n========================================\n");
    printf("MAX78000 LED Demo\n");
    printf("3x3 LED Matrix (9 LEDs)\n");
    printf("========================================\n\n");

    printf("Initializing %d LEDs...\n", NUM_LEDS);
    led_init();
    button_init();
    printf("Initialization complete.\n\n");

    printf("Testing LEDs...\n");
    for (int i = 0; i < NUM_LEDS; i++) {
        printf("  LED %d\n", i);
        led_on(i);
        MXC_Delay(MXC_DELAY_MSEC(200));
        led_off(i);
    }
    printf("Test complete.\n\n");

while (1) {
    // If button pressed → switch mode
    if (button_pressed()) {
        mode = !mode;
        printf("Mode changed: %s\n", mode ? "Snake" : "Heartbeat");
        MXC_Delay(MXC_DELAY_MSEC(300)); // prevent fast toggling
    }

    if (mode == 0) {
        heartbeat_pattern();
    } else {
        snake_pattern();
    }
}

}
