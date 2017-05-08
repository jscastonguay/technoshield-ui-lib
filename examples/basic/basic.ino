#include <Technoshield-ui.h>

Technoshield_ui ui(0,0);

void setup() {
  ui.begin();
  ui.print("hello, world!");
}

void loop() {
   ui.setCursor(0, 1);
  // print the number of seconds since reset:
  ui.print(millis()/1000);

  ui.setBacklight(HIGH);
  delay(500);
  ui.setBacklight(LOW);
  delay(500);

}
