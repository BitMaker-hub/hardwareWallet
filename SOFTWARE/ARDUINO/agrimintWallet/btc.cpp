#include <Arduino.h>
#include <EEPROM.h>
#include "btc.h"
#include "Bitcoin.h"
#include "GlobalVARS.h"

extern sWallet myWallet;

String password="";

/**************🍃 INIT WALLET *******************/
void initWallet(void){

  if(myWallet.mnemonic.length() > 0){
    HDPrivateKey hd(myWallet.mnemonic, password);
    HDPrivateKey account = hd.derive("m/84'/0'/0'/");
    
    myWallet.xpub= account.xpub();
  }

}

void createSeed(void){

  // entropy bytes to mnemonic
  uint8_t arr[512] = {0};
  random_buffer(arr, 512);
  String mn = generateMnemonic(arr, sizeof(arr));
  Serial.println(mn);

  // Extract xpub from primary address
  HDPrivateKey hd(mn, password);
  HDPrivateKey account = hd.derive("m/84'/0'/0'/");
    
  myWallet.xpub= account.xpub();
  myWallet.mnemonic = mn;
}

void saveMnemonic(String mnemonic){

  uint16_t i;
  for(i=2; i<(mnemonic.length()+2); i++){
    EEPROM.write(i, mnemonic[i-2]);
  }
  EEPROM.write(i,3);
  EEPROM.write(1,STX);
  delay(10);
  EEPROM.commit();
}


