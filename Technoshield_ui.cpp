#include "Technoshield_ui.h"

constexpr uint8_t Technoshield_ui::LED_PINMUX[NB_OF_LED];
constexpr uint8_t Technoshield_ui::BUT_PINMUX[NB_OF_BUTTONS];
  
Technoshield_ui::Technoshield_ui( uint8_t lcdA1, uint8_t lcdA0, uint8_t butLedA1, uint8_t butLedA0) :
  Adafruit_LiquidCrystal( ((lcdA1 & 1) << 1) + (lcdA0 & 1)),
  ledButtonAddress( MCP23008_ADDRESS + BUT_LED_MCP23008_ADDR_OFFSET + ((butLedA1 & 1) << 1) + (butLedA0 & 1)) {
}

Technoshield_ui::Technoshield_ui( uint8_t ldcSubAddr, uint8_t butLedSubAddr) :
  Adafruit_LiquidCrystal( ldcSubAddr),
  ledButtonAddress( MCP23008_ADDRESS + BUT_LED_MCP23008_ADDR_OFFSET + butLedSubAddr) {
}

void Technoshield_ui::begin() {
  Adafruit_LiquidCrystal::begin( 16, 2);
  ledButton.begin( ledButtonAddress);
  
  for (uint8_t i = 0; i < NB_OF_LED; i++) {
    ledButton.pinMode( LED_PINMUX[i], OUTPUT);
  }
  
  for (uint8_t i = 0; i < NB_OF_BUTTONS; i++) {
    ledButton.pinMode( BUT_PINMUX[i], INPUT);
    ledButton.pullUp( BUT_PINMUX[i], true);
  }
}

uint8_t Technoshield_ui::isButtonPressed( uint8_t button) {
  
  uint8_t state = 0;
  
  button--;
  if (button < NB_OF_BUTTONS) {
    // Inverse logic
    state = (ledButton.digitalRead( BUT_PINMUX[button]) == false);
  }
  
  return state;
}

void Technoshield_ui::setLedState( uint8_t led, uint8_t state) {
  
  led--;
  if (led < NB_OF_LED) {
    ledButton.digitalWrite( LED_PINMUX[led], state);
  }
}
