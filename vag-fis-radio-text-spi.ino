#include "VAGFISRadioText.hpp"

VAGFISRadioText LCD(5);

void setup() {
  LCD.init();
}

void loop() {
  LCD.showText("Line 1", "Line 2");
  delay(500);
  // LCD.sendKeepAlive();
}
