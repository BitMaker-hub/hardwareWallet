#include "gpio.h"
#include "btc.h"
#include "workflow.h"
#include "GlobalVARS.h"

sWallet myWallet;

void setup() {

  pinMode(PIN_MOVE, INPUT_PULLUP);              // Init pushbutton pin
  pinMode(PIN_SELECT, INPUT_PULLUP);            // Init pushbutton pin
  Serial.begin(SERIAL_BAUD);                    // Init Serial port
  EEPROMsetup();                                // Init EEPROMdata
  Init_TFT();                                   // Init TFT wallet
  initWallet();                                 // Init wallet data
}


void loop() {
  while(true){
    int buttonState = checkButton();

    switch(myWallet.State){
      case STATE_MENU:    doMenuState(buttonState); break;
      case STATE_NEWSEED: doNewSeed(buttonState); break;
    }
    delay(10);
  }
}
