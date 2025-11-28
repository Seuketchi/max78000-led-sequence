## MAX78000 LED Demo — 3×3 LED Matrix

A firmware demonstration for the MAX78000 platform featuring a 3×3 LED matrix (9 LEDs), two visual patterns (Heartbeat and Snake), and button-driven mode switching. This project emphasizes clean code organization with a dedicated LED abstraction module (`led.c`/`led.h`).

**Developed with CodeFusion Studio**

## Features

- **3×3 LED Matrix Control**: 9 LEDs arranged in a 3×3 grid with clean GPIO abstraction.
- **Two Display Modes**:
  - **Heartbeat** (default): All LEDs flash in a heartbeat rhythm (100 ms on, 100 ms on, 600 ms off).
  - **Snake**: A snake-like chase pattern moving left-to-right, right-to-left, and top-to-bottom across the matrix.
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

The `led.c`/`led.h` module provides:

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

## Hardware Setup

- **Button**: Connected to `BUTTON_PORT` (MXC_GPIO1) and `BUTTON_PIN` (MXC_GPIO_PIN_7); active LOW.
- **LEDs**: 9 discrete GPIOs mapped in `led.c`. Verify pin assignments match your board configuration.
- **UART**: Console output at 115200 8-N-1 for startup messages and mode change prints.

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
| Button not responsive | Confirm `BUTTON_PORT`/`BUTTON_PIN` in `main.c` match your button wiring; test active LOW logic. |
| Build fails | Ensure `arm-none-eabi` toolchain and `make` are installed and on your `PATH`. |

## References

- **MSDK User Guide**: https://analogdevicesinc.github.io/msdk/USERGUIDE/
- **MAX78000 Datasheet**: See MSDK documentation for detailed GPIO and board information.

## License

See project root for license information.