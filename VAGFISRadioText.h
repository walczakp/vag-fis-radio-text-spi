#ifndef VAGFISRadioText_h
#define VAGFISRadioText_h

#include <Arduino.h>
#include <SPI.h>

#define KEEP_ALIVE 0xC3
#define WRITE_START 0x0F
#define KEEP_ALIVE_DELAY_TIME 500

class VAGFISRadioText {
  public:
    VAGFISRadioText(int enablePin);
    void init();
    void showText(const char* line0, const char* line1);
    void sendKeepAlive();
  
  private:
    int ena;
    unsigned long lastSendTime;

    void sendByte(uint8_t byteVal);
    void enableStart();
    void enableStop();
    void beginTransaction();
    void endTransaction();
};

#endif
