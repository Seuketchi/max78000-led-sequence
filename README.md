# MAX78000 3×3 LED Matrix Demo

A demonstration project for the MAX78000 microcontroller implementing LED sequencing on a custom **3×3 LED matrix**. The application showcases GPIO control, software PWM fading, button-driven mode switching, and two primary LED animation patterns.

**Developed with CodeFusion Studio**

## Overview

This project demonstrates practical GPIO control, timing, and embedded pattern sequencing on the MAX78000 platform. It drives **9 discrete LEDs** arranged in a 3×3 grid with a push-button allowing runtime switching between two animation modes:

1. **Heartbeat Pattern** – A pulsing effect mimicking a heartbeat.
2. **Snake Pattern** – A multi-segment snake that traverses the 3×3 matrix in a sequential pattern (left-to-right, right-to-left, top-to-bottom).

![LED Matrix Demo](demo.gif)

The implementation uses:

- Maxim Integrated's **MXC GPIO APIs**
- **MXC_Delay** for timing and software PWM
- **Clean LED abstraction** (`led.c`/`led.h`) for modular GPIO control
- Simple **software debounce** routine for the button

This serves as a template for beginners working with LED animations, GPIO control, and embedded pattern sequencing on MAX78000.

## Features

- **3×3 LED Matrix Control**: 9 LEDs with clean GPIO abstraction module.
- **Two Display Modes**:
  - **Heartbeat** (default): All LEDs flash in a heartbeat rhythm (100 ms on, 100 ms on, 600 ms off).
  - **Snake**: A 3-segment snake that chases across the matrix.
- **Button Mode Switching**: Push button (active LOW with debounce) toggles between modes; mode change is logged to UART.
- **Startup Diagnostics**: Console banner, LED initialization confirmation, and individual LED test sequence.

## Project Structure

```
main.c              - Application logic (patterns, button handling, main loop)
led.h               - LED module public API
led.c               - LED driver (GPIO control, pin mapping)
gpio.c/gpio.h       - Low-level GPIO abstraction (provided by MSDK)
Makefile            - Build configuration
README.md           - This file
```

## LED Module API (`led.h`)

The `led.c`/`led.h` module provides a clean abstraction:

```c
void led_init(void);           // Initialize all LEDs as GPIO outputs
void led_on(int i);            // Turn on LED i (0..8)
void led_off(int i);           // Turn off LED i (0..8)
void led_toggle(int i);        // Toggle LED i (0..8)
void all_leds_on(void);        // Turn on all LEDs
void all_leds_off(void);       // Turn off all LEDs
void fade_led(int led, int fade_in);  // Software PWM fade in/out
```

**LED Layout** (3×3):
```
[0] [1] [2]
[3] [4] [5]
[6] [7] [8]
```

Pin mappings are defined statically in `led.c` and can be adjusted there.

## Hardware Requirements

- **MAX78000FTHR** or MAX78000 evaluation board
- **9 LEDs** wired according to the pin mapping defined in `led.c`
- **1 momentary push-button** connected to GPIO1.7 (active LOW)
- Current-limiting resistors for all LEDs

### Pin Mapping

- **Button**: `BUTTON_PORT` (MXC_GPIO1) and `BUTTON_PIN` (MXC_GPIO_PIN_7); active LOW
- **LEDs**: 9 discrete GPIOs defined in `led.c` static array `leds[]`
- **UART**: Console output at 115200 8-N-1

## Build & Flash

From the project root:

```powershell
make
make flash
```

The `Makefile` is pre-configured for the MAX78000EVKIT. Adjust `BOARD` or board-specific settings if using a different board.

## Running the Demo

1. **Build and flash** the firmware to your board.
2. **Open a serial terminal** at 115200 8-N-1 to observe startup messages:
   ```
   ========================================
   MAX78000 LED Demo
   3x3 LED Matrix (9 LEDs)
   ========================================

   Initializing 9 LEDs...
   Initialization complete.

   Testing LEDs...
     LED 0
     LED 1
     ...
   Test complete.
   ```
3. **Observe the pattern** (Heartbeat by default).
4. **Press the button** to switch to Snake mode and back; the console will print the new mode.

## Troubleshooting

| Issue | Solution |
|-------|----------|
| No serial output | Verify COM port, UART jumpers/pins, and terminal baud rate (115200). |
| LEDs not lighting | Check GPIO pin mappings in `led.c` match your hardware; verify GPIO initialization. |
| Button not responsive | Confirm `BUTTON_PORT`/`BUTTON_PIN` match your button wiring; test active LOW logic. |
| Build fails | Ensure `arm-none-eabi` toolchain and `make` are installed and on your `PATH`. |

## References

- MAX78000FTHR Board Documentation: [https://www.analog.com/en/resources/evaluation-hardware-and-software/evaluation-boards-kits/max78000fthr.html](https://www.analog.com/en/resources/evaluation-hardware-and-software/evaluation-boards-kits/max78000fthr.html)
- MAX78000 Datasheet: [https://www.analog.com/media/en/technical-documentation/data-sheets/max78000.pdf](https://www.analog.com/media/en/technical-documentation/data-sheets/max78000.pdf)
- **MSDK User Guide**: https://analogdevicesinc.github.io/msdk/USERGUIDE/

## Future Enhancements

Potential improvements and planned features:

- Add more animations (ripple, spiral, binary counter)
- Implement brightness control using hardware PWM
- Add debounced interrupt-based button handling
- Integrate with RTOS for task-based LED control
- Additional LED sequences and advanced patterns

## License

See project root for license information.