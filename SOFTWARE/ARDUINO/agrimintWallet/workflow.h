#include <Arduino.h>


/**********🍃 WORKFLOW FUNCTIONS ****************/
void doMenuState(int keyState);
void doNewSeed(int keyState);
  
/**********🍃 WORKFLOW MENU ****************/
#define maxMenu     5 //Number of options in menu starting from 0
static String menuList[]={"Create new Seed",
                          "Import Seed",
                          "Show Seed",
                          "Display Address",
                          "Export ZPUB",
                          "Sign Transaction"};
