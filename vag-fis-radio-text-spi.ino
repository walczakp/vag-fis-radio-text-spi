#include "VAGFISRadioText.h"

#define pinENABLE 5
VAGFISRadioText LCD(pinENABLE);

void setup() {
  LCD.init();
}

void loop() {
  LCD.showText("Line 1", "Line 2");
  delay(500);
  // LCD.sendKeepAlive();
}