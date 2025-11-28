/******************************************************************************
 * LED Abstraction Module Implementation
 * Manages 3x3 LED matrix (9 LEDs) on MAX78000
 ******************************************************************************/

/***** Includes *****/
#include "led.h"
#include "gpio.h"
#include "mxc_delay.h"

/***** LED Pin Mapping *****/

typedef struct {
    mxc_gpio_regs_t *port;
    uint32_t pin;
} led_pin_t;

/**
 * LED layout (3×3):
 *
 *  [0] [1] [2]
 *  [3] [4] [5]
 *  [6] [7] [8]
 */

// Pin mapping for each LED
static const led_pin_t leds[NUM_LEDS] = {
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

/***** Public Function Implementations *****/

void led_init(void)
{
    for (int i = 0; i < NUM_LEDS; i++) {
        gpio_init_output(leds[i].port, leds[i].pin);
        gpio_clear(leds[i].port, leds[i].pin);
    }
}

void led_on(int i)
{
    if (i >= 0 && i < NUM_LEDS) {
        gpio_set(leds[i].port, leds[i].pin);
    }
}

void led_off(int i)
{
    if (i >= 0 && i < NUM_LEDS) {
        gpio_clear(leds[i].port, leds[i].pin);
    }
}

void led_toggle(int i)
{
    if (i >= 0 && i < NUM_LEDS) {
        gpio_toggle(leds[i].port, leds[i].pin);
    }
}

void all_leds_off(void)
{
    for (int i = 0; i < NUM_LEDS; i++) {
        gpio_clear(leds[i].port, leds[i].pin);
    }
}

void all_leds_on(void)
{
    for (int i = 0; i < NUM_LEDS; i++) {
        gpio_set(leds[i].port, leds[i].pin);
    }
}

void fade_led(int led, int fade_in)
{
    // fade_in = 1 → fade-in
    // fade_in = 0 → fade-out

    for (int level = 0; level < 100; level++) {
        int duty = fade_in ? level : (100 - level);

        // Software PWM cycle
        for (int t = 0; t < 100; t++) {
            if (t < duty) {
                gpio_set(leds[led].port, leds[led].pin);
            } else {
                gpio_clear(leds[led].port, leds[led].pin);
            }
            
            // small delay for PWM speed
            MXC_Delay(MXC_DELAY_USEC(50));
        }
    }
}
