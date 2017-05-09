#ifndef TECHNOSHIELD_UI
#define TECHNOSHIELD_UI

#include "utility/Adafruit_LiquidCrystal.h"
#include <Wire.h>

#define JUMPER_CLOSE  1
#define JUMPER_OPEN   0

#define NB_OF_LED      3
#define NB_OF_BUTTONS  5 

class Technoshield_ui : public Adafruit_LiquidCrystal {
	
	public:
	Technoshield_ui( unsigned int lcdA1, unsigned int lcdA0, unsigned int butLedA1, unsigned int butLedA0);
	Technoshield_ui( unsigned int ldcSubAddr = 0, unsigned int butLedSubAddr = 0);
	void begin();
	uint8_t isButtonPressed( uint8_t button);
	void setLedState( uint8_t led, uint8_t state);
	
	private:
	Adafruit_MCP23008 ledButton;
  uint8_t ledButtonAddress;
  
  static constexpr uint8_t LED_PINMUX[NB_OF_LED] = { 2, 1, 0};
  static constexpr uint8_t BUT_PINMUX[NB_OF_BUTTONS] = { 7, 6, 5, 4, 3};
  static const uint8_t BUT_LED_MCP23008_ADDR_OFFSET = 4;
};

#endif