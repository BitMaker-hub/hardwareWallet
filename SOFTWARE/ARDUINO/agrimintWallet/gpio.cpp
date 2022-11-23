#include <EEPROM.h>
#include "GlobalVARS.h"
#include "gpio.h"
#include "Wire.h"
#include "workflow.h"
#include <TFT_eSPI.h> // Graphics and font library for ST7735 driver chip


extern TFT_eSPI tft = TFT_eSPI();  // Invoke library, pins defined in User_Setup.h
extern sWallet myWallet;

/***********************🍃 EEPROM DATA ******************************/

void EEPROMsetup(){
  
  EEPROM.begin(EEPROM_SIZE);
   
  /********🍃 READ MNMONIC ************/
  String mnemonic="";
  if(EEPROM.read(1) == STX){
    for(uint16_t i=2; i<400; i++){
      uint8_t nm = EEPROM.read(i);
      if(nm == ETX) break;
      mnemonic = mnemonic + char(nm);
    }
  }
  myWallet.mnemonic = mnemonic;
  Serial.print("Current mnemonic: "); Serial.println(mnemonic);
  
}


/*****************🍃 TFT WORK *********************/

void Init_TFT(void){

  /******** INIT DISPLAY ************/
  tft.init();
  tft.setRotation(1);
    
  /******** PRINT INIT SCREEN *****/
  tft.fillScreen(TFT_BLACK);
  tft.setSwapBytes(true);// Swap the colour byte order when rendering
  tft.pushImage(20, 35, logoWidth, logoHeight, agrimintLogo);
  
  tft.setTextColor(0x2E6E);
  tft.setTextDatum(ML_DATUM); //MIDDLE CENTER - MC_DATUM / TOP CENTER - TC_DATUM
  tft.setFreeFont(FMBO12);
  tft.drawString("AGRIMINT", 90 , 50, GFXFF); 
  tft.setTextColor(TFT_WHITE);
  tft.setFreeFont(FMBO9);
  tft.drawString("WALLET", 90 , 75, GFXFF); 
  
  delay(3000);
  
  //Draw menu
  tft.fillScreen(TFT_BLACK);
  tft.fillRect(0, 0, D_ANCHO, HEADER_HEIGHT-1, 0x2E6E); //Delete icon area 
  tft.setFreeFont(FMB9);        // Select font 1 which is the Adafruit GLCD font
  tft.setTextColor(TFT_BLACK);
  tft.drawString("AGRIMINT WALLET", 5, (HEADER_HEIGHT/2) - 1, GFXFF);
  tft.setCursor (0, HEADER_HEIGHT+2);
  tft.setTextFont(2); 
  int i=0;
  for(i=0; i<maxMenu; i++){
    if(myWallet.preState == i){
      tft.setTextColor(0x2E6E);
    }
    else{
      tft.setTextColor(TFT_WHITE);
    }
    tft.println(menuList[i]);
  }
  myWallet.preState = 0;
  
  //pinMode(4,OUTPUT); //Pin backlight

}

/*****************🍃 BUTTON DETECTION *********************/
byte butLst;

int checkButton (void)
{
    bool   butReleased = false;
    const  unsigned long ButTimeout    = 250;
    const  unsigned long ButLongClick  = 5000;
    static unsigned long msecLst;
           unsigned long msec = millis ();

    byte but = digitalRead (PIN_SELECT);
    if (butLst != but)  {
        butLst = but;
        delay (10);           // **** debounce

        if (LOW == but)  {   // press
            if (msecLst)  { // 2nd press
                msecLst = 0; 
                return DoubleClick;
            }
            else
                msecLst = 0 == msec ? 1 : msec;
        }
    }

    int elapsed = msec - msecLst;
    if (msecLst && (elapsed > ButTimeout) && (elapsed < ButLongClick))  {
        if(but != LOW) {
          msecLst = 0; 
          return SingleClick;
        }
    }

    //LongClick
    if((but == butLst) && (but == LOW)) {
        if(elapsed > ButLongClick) {        
          msecLst = 0; 
          return LongClick;
        }
    }
    
    return None;
}
// -----------------------------------------------------------------------------


