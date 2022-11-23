#include <Arduino.h>
#include <EEPROM.h>
#include "gpio.h"
#include "btc.h"
#include "GlobalVARS.h"
#include "workflow.h"
#include <TFT_eSPI.h> // Graphics and font library for ST7735 driver chip


extern TFT_eSPI tft;  // Invoke library, pins defined in User_Setup.h
extern sWallet myWallet;


/**************🍃 WORKSATES *********************
  🍃🍃🍃🍃🍃🍃🍃🍃🍃🍃🍃🍃🍃🍃🍃🍃🍃🍃🍃🍃🍃🍃🍃🍃🍃🍃🍃
 ***********************************************/

/**************🍃 MENU *****************/
void doMenuState(int keyState){
  if(keyState == SingleClick) {
    myWallet.preState++;
    if(myWallet.preState>maxMenu) myWallet.preState=0;
    
    tft.fillScreen(TFT_BLACK);
    tft.fillRect(0, 0, D_ANCHO, HEADER_HEIGHT-1, 0x2E6E); //Delete icon area 
    tft.setFreeFont(FMB9);        // Select font 1 which is the Adafruit GLCD font
    tft.setTextColor(TFT_BLACK);
    tft.drawString("AGRIMINT WALLET", 5, (HEADER_HEIGHT/2) - 1, GFXFF);
    tft.setCursor (0, HEADER_HEIGHT+2);
    tft.setTextFont(2); 
    for(uint8_t i=0; i<maxMenu; i++){
      if(myWallet.preState == i){
        tft.setTextColor(0x2E6E);
      }
      else{
        tft.setTextColor(TFT_WHITE);
      }
      tft.println(menuList[i]);
    }
  }
}

/**************🍃 NEW SEED *****************/
void doNewSeed(int keyState){
  createSeed();

}


