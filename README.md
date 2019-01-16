# Technoshield User Interface - SW Library

This library drives the Technoshield User Interface board (https://github.com/jscastonguay/technoshield-ui-hw).
It is based on two libraries devepped by Adafruit which are

- [Adafruit LiquidCrystal](https://github.com/adafruit/Adafruit_LiquidCrystal)
- [Adafruit MCP23008 library](https://github.com/adafruit/Adafruit-MCP23008-library)

Both are already included in the Technoshield User Interface SW Library.
See the following link for further details: [Technoshield Hackaday project](https://hackaday.io/project/21892-technoshield-user-interface)

## Installation

Follow this [instruction](https://www.arduino.cc/en/guide/libraries) and look for *technoshield*.

## Application Programming Interface (API)

### User Interface Instantiation and Initialisation

Start by first create a user interface (ui) instance as follows:

```Arduino
Technoshield_ui ui(JUMPER_OPEN, JUMPER_OPEN, JUMPER_OPEN, JUMPER_OPEN);
```

where each parameter can be either `JUMPER_OPEN` or `JUMPER_CLOSE`. The parameters correspond to the state of `I2C Addr` jumpers located on the Technoshield board following the same order from left to right:

1. LCD A1
2. LCD A0
3. Button/LED A1
4. Button/LED A0

These jumpers are used to change the I2C addresses of the LCD and buttons/LED which are

| __Function__    | __I2C Address Range__ |
|-------------    |-------------------    |
| LCD             | 0x20 to 0x23          |
| Buttons/LED     | 0x24 to 0x27          |

Note that the creation can be done also as follows:
```Arduino
Technoshield_ui ui(0, 0);
```

where the parameters correspond to the I2C subaddresses (0 to 3) made by the jumers' states. Installing a jumper sets VCC to the corresponding subaddress pins. So, the subaddress is 0 if both `LCD A1` and `LCD A0` are opened, is 1 if `LCD A1` is opened but `LCD A0` closed, and so on.

Finally, if all jumpers' states are open (meaning 0 as I2C subaddress for both LCD and Buttons/LED), the following can be used:

```Arduino
Technoshield_ui ui;
```

After the user interface object has been created, it must be initialised in the `setup` function as follows:

```Arduino
void setup() {
  ui.begin();
}
```

### LCD and SD Card

Almost all functions of the standard Arduino Liquid Crystal library are supported. For examples:

```Arduino
 ui.print("hello, world!");
 ui.setCursor(0, 1);
 ui.setBacklight(true);
```

See the [LiquidCrystal](https://www.arduino.cc/en/Reference/LiquidCrystal) library for further details.

For SD card usage, use the standard SD library. Note that the SD card *Slave Select* is connected to the Arduino's pin 10.
See the [SD Library](https://www.arduino.cc/en/reference/SD) for further details.

### Buttons and LED

The following functions can be used to drive the buttons and the LED.

__isButtonPressed(button)__

This function returns `true` if a given `button` is pressed. `button` is from 1 (the button named SW1) to 5 (the button named SW5).

__setLedState(led, state)__

This function turns on and off a given `LED`. `LED` is from 1 (the LED named D1) to 3 (the LED named D3). The `state` can be 0, 1, `false`, `true`, `LOW`, `HIGH`, etc.

## Example

Here is a basic example. The buttons 1 to 3 (SW1 to SW3) turn on one of LED, the button 4 (SW4) turn on the LCD backlight while the button 5 (SW5) turn off the LED and the backlight. Note that in this example all I2C Addr jumpers are opened.

```Arduino
#include <Technoshield_ui.h>

Technoshield_ui ui(JUMPER_OPEN, JUMPER_OPEN, JUMPER_OPEN, JUMPER_OPEN);

unsigned long timeout = 0;

void setup() {
  ui.begin();
  ui.print("hello, world!");
}

void loop() {

  // Print the number of seconds since reset:
  if (millis() > timeout + 1000) {
    timeout = millis();
    ui.setCursor(0, 1);
    ui.print(millis() / 1000);
  }

  // Turn-on LED or backlight according to buttons 1 to 4.
  if (ui.isButtonPressed(1)) {
    ui.setLedState(1, true);
  }

  if (ui.isButtonPressed(2)) {
    ui.setLedState(2, true);
  }

  if (ui.isButtonPressed(3)) {
    ui.setLedState(3, true);
  }

  if (ui.isButtonPressed(4)) {
    ui.setBacklight(true);
  }

  // Turn-off everything.
  if (ui.isButtonPressed(5)) {
    for (int i = 1; i <= NB_OF_LED; i++) {
      ui.setLedState(i, false);
    }
    ui.setBacklight(false);
  }
}
```
