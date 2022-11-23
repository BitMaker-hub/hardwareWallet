#include <stdint.h>
#include <Arduino.h>

#define byte uint8_t
/**********************************
 🍃 IO PINs
**********************************/
#define BUTTON_PIN			  45  		// Button pin
#define LED_PIN           38      // Pin - leds neopixel
#define LED_COUNT         3       // Neopixel number of leds
#define I2C_SDA           41      // SDA I2C pin
#define I2C_SCL           39      // SCL I2C pin
#define LOW_POWER                 // Accelerometer mode

/**********************************
 🍃 DEFINITIONS
**********************************/
//🍃 WORKING STATES
enum { None, SingleClick, DoubleClick, LongClick };

/**********************************
 🍃 GENERAL
**********************************/
#define SERIAL_BAUD       115200   // baudrate debug
#define EEPROM_SIZE       400      // define the number of bytes you want to access
#define MNEMONIC_VOID     0        // first byte of mnemonic represents mnemonic state 
#define STX               2        // Start of text
#define ETX               3        // end of text

const int wdtTimeout = 3000;  //time in ms to trigger the watchdog

/***************🍃 BUTTONS ***************/
#define PIN_MOVE          0
#define PIN_SELECT        35

/***************🍃 SCREEN ***************/
#define D_ANCHO           240     // screen width
#define D_ALTO            128     // screen height
#define D2_ANCHO          125     // half screen width
#define D2_ALTO           64     // half screen height
#define HEADER_HEIGHT     25

/********** 🍃 STATES ************************/
#define STATE_MENU        1
#define STATE_NEWSEED     2
/**********************************/

//🍃 Global vars 
typedef struct {
   uint8_t State;           //Pill initStatus [Virgin, Locked, Unlocked]
   uint8_t preState;         //Current menu position before selecting it
   String xpub;             //Current xpub address
   String mnemonic;         //Current words
}sWallet;

/*********************************************************************************
**                            End Of File
*********************************************************************************/


