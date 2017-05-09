#include <Technoshield-ui.h>

Technoshield_ui ui(0, 0);
//Adafruit_LiquidCrystal ui(0);

unsigned long timeout = 0;

void setup() {
  ui.begin();
  ui.print("hello, world!");
}

void loop() {

  if (millis() > timeout + 1000) {
    ui.setCursor(0, 1);
    // print the number of seconds since reset:
    ui.print(millis() / 1000);
  }

  ui.setLedState(1, ui.isButtonPressed(1));
  ui.setLedState(2, ui.isButtonPressed(2));
  ui.setLedState(3, ui.isButtonPressed(3));

  ui.setBacklight(ui.isButtonPressed(4));
}
