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
#include "led.h"

/***** Definitions *****/

#define BUTTON_PORT MXC_GPIO1
#define BUTTON_PIN  MXC_GPIO_PIN_7

int mode = 0;  // 0 = heartbeat, 1 = snake

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


/***** Patterns - now return 1 if button pressed *****/

int heartbeat_pattern(void)
{
    all_leds_on();
    MXC_Delay(MXC_DELAY_MSEC(100));
    if (button_pressed()) return 1;
    
    all_leds_off();
    MXC_Delay(MXC_DELAY_MSEC(100));
    if (button_pressed()) return 1;

    all_leds_on();
    MXC_Delay(MXC_DELAY_MSEC(100));
    if (button_pressed()) return 1;
    
    all_leds_off();
    MXC_Delay(MXC_DELAY_MSEC(600));
    if (button_pressed()) return 1;
    
    return 0;
}

int snake_pattern(void)
{
    // 3x3 snake path (L→R, R→L, top→bottom)
    int snake_path[NUM_LEDS] = {
        0, 1, 2,   // top row
        5, 4, 3,   // middle row (reverse)
        6, 7, 8    // bottom row
    };

    all_leds_off();

    // Snake with trailing body (length 3)
    #define SNAKE_BODY_LENGTH 3
    int snake_body[SNAKE_BODY_LENGTH];
    for (int i = 0; i < SNAKE_BODY_LENGTH; i++) {
        snake_body[i] = -1;  // -1 means inactive
    }

    for (int i = 0; i < NUM_LEDS; i++) {
        // Check button before each LED
        if (button_pressed()) return 1;

        // Shift body back (tail disappears, new segments push from head)
        for (int j = SNAKE_BODY_LENGTH - 1; j > 0; j--) {
            snake_body[j] = snake_body[j - 1];
        }
        snake_body[0] = snake_path[i];  // Add head to front

        // Turn off the tail (last element)
        if (snake_body[SNAKE_BODY_LENGTH - 1] >= 0) {
            led_off(snake_body[SNAKE_BODY_LENGTH - 1]);
        }

        // Draw the entire snake body (head brightest, tail dimmer effect via timing)
        for (int j = 0; j < SNAKE_BODY_LENGTH; j++) {
            if (snake_body[j] >= 0) {
                led_on(snake_body[j]);
            }
        }

        MXC_Delay(MXC_DELAY_MSEC(150));
        
        // Check button after delay
        if (button_pressed()) return 1;
    }

    // Turn off remaining snake body
    all_leds_off();

    MXC_Delay(MXC_DELAY_MSEC(200));
    if (button_pressed()) return 1;
    
    return 0;
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
        int button_pressed_flag = 0;
        
        if (mode == 0) {
            button_pressed_flag = heartbeat_pattern();
        } else {
            button_pressed_flag = snake_pattern();
        }
        
        // If button was pressed during pattern, switch mode immediately
        if (button_pressed_flag) {
            all_leds_off();  // Clean slate
            mode = !mode;
            printf("Mode changed: %s\n", mode ? "Snake" : "Heartbeat");
            MXC_Delay(MXC_DELAY_MSEC(300)); // prevent fast toggling
        }
    }
}