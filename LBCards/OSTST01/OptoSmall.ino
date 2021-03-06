/*
 OptoSmall.ino
*/

#include "Wire.h"

#include "MyMenu.h"

#include "U8glib.h"

//////////////////////////////////////////////////////////////////////////////
// enums follow
//////////////////////////////////////////////////////////////////////////////

enum MENUITEMS
{
  FIRST_LINE_MENU,
  SECOND_LINE_MENU,
  THIRD_LINE_MENU,
  FOURTH_LINE_MENU,
  FIRST_SUB_MENU,
  SECOND_SUB_MENU,
  FSTL_TESTS_MENU,
  SCND_TESTS_MENU
};

//////////////////////////////////////////////////////////////////////////////
// Global variables follow
//////////////////////////////////////////////////////////////////////////////

unsigned long testCount;
unsigned long passCount;
unsigned long failCount;

uint8_t menuState;              // Menu State variable

U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NO_ACK);

MyMenu menuCard;

#define LCD_COLUMNS 14

void setup(void) 
{
  int loopCnt;
  menuState = FIRST_LINE_MENU;  // Set up the init menu state
  displayInit();                // Hardware specific function to set up the display
  menuCard.begin(1);            // pass the address of the mcp23008 on the menu card
  TWBR = 12;                    // 400 KHz I2C
  for (loopCnt = 3; loopCnt < 7; loopCnt++)
    pinMode(loopCnt, INPUT);
  for (loopCnt = 7; loopCnt < 11; loopCnt++)
    pinMode(loopCnt, OUTPUT);
}

void loop(void) 
{
  u8g.firstPage();  
  do 
  {
    menuRefresh();
  } 
  while( u8g.nextPage() );

  menuNav();
}

//////////////////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////////////////

void initTests(void)
{
  testCount = 0;
  passCount = 0;
  failCount = 0;
}

