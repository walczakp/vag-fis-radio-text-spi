#include "VAGFISRadioText.hpp"

VAGFISRadioText::VAGFISRadioText(int enablePin) {
  ena = enablePin;
  lastSendTime = millis();
}

void VAGFISRadioText::init() {
  pinMode(ena, OUTPUT);
  digitalWrite(ena, LOW);
  SPI.begin();
}

void VAGFISRadioText::showText(const char* line0, const char* line1) {
  char l0[8] = "       ";
  char l1[8] = "       ";
  strncpy(l0, line0, 8);
  strncpy(l1, line1, 8);

  for (int i = 0; i < 8; i++) {
    l0[i] = toupper(l0[i]);
    l1[i] = toupper(l1[i]);
  }

  uint8_t dataCRC = (0xFF ^ WRITE_START);

  beginTransaction();
  sendByte(WRITE_START);

  for (int i = 0; i < 8; i++) {
    sendByte(0xFF ^ l0[i]);
    dataCRC += l0[i];
  }

  for (int i = 0; i < 8; i++) {
    sendByte(0xFF ^ l1[i]);
    dataCRC += l1[i];
  }

  sendByte(dataCRC % 0x100);
  endTransaction();
  lastSendTime = millis();
}

void VAGFISRadioText::sendKeepAlive() {
  if (millis() - lastSendTime < KEEP_ALIVE_DELAY_TIME) return;

  beginTransaction();
  sendByte(0xFF ^ KEEP_ALIVE);
  endTransaction();
  lastSendTime = millis();
}

void VAGFISRadioText::sendByte(uint8_t byteVal) {
  SPI.transfer(byteVal);
  delayMicroseconds(100);
}

void VAGFISRadioText::enableStart() {
  digitalWrite(ena, HIGH);
}

void VAGFISRadioText::enableStop() {
  digitalWrite(ena, LOW);
}

void VAGFISRadioText::beginTransaction() {
  enableStart();
  SPI.beginTransaction(SPISettings(125000, MSBFIRST, SPI_MODE3));
  delayMicroseconds(100);
}

void VAGFISRadioText::endTransaction() {
  SPI.endTransaction();
  delayMicroseconds(150);
  enableStop();
}
