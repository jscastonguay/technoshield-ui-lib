#include "Technoshield-ui.h"

// Technoshield_ui::Technoshield_ui( unsigned int lcdA1, unsigned int lcdA0, unsigned int butLedA1, unsigned int butLedA0) :
  // Adafruit_LiquidCrystal( (lcdA1 << 1) + lcdA0),
  // ledButtonAddress( MCP23008_ADDRESS + (butLedA1 << 1) + butLedA0) {
// }
  
Technoshield_ui::Technoshield_ui( unsigned int ldcSubAddr, unsigned int butLedSubAddr) :
  Adafruit_LiquidCrystal( ldcSubAddr),
  ledButtonAddress( MCP23008_ADDRESS + butLedSubAddr) {
}

void Technoshield_ui::begin() {
  Adafruit_LiquidCrystal::begin( 16, 2);
  ledButton.begin( ledButtonAddress);
  
  for (int i = 0; i < NB_OF_LED; i++) {
    ledButton.pinMode( ledPinmux[i], OUTPUT);
  }
  
  for (int i = 0; i < NB_OF_BUTTONS; i++) {
    ledButton.pinMode( butPinmux[i], INPUT);
    ledButton.pullUp( butPinmux[i], true);
  }
}

uint8_t Technoshield_ui::isButtonPressed( uint8_t button) {
  
  uint8_t state = 0;
  
  button--;
  if (button < NB_OF_BUTTONS) {
    state = ledButton.digitalRead( butPinmux[button]);
  }
  
  return state;
}

uint8_t Technoshield_ui::isButtonStateChanged( uint8_t button) {
  return false;
}

void Technoshield_ui::setLedState( uint8_t led, uint8_t state) {
  
  led--;
  if (led < NB_OF_LED) {
    ledButton.digitalWrite( ledPinmux[led], state);
  }
}
