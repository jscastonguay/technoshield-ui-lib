/* Technoshield basic example.
 *  
 * The button 1 to 3 (SW1 to SW3) turn on a LED, the button 4 (SW4) turn on
 * the LCD backlight while the button 5 (SW5) turn off the LED and the backlight.
 * 
 * Note that in this example all I2C Addr jumpers are opened.
 */

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
