#include <Arduino.h>

#include <Wire.h>
#include <MD_MAX72xx.h>
#include <MD_Parola.h>

#define DATAPIN 8
#define CSPIN 9
#define CLKPIN 10

uint8_t numDisplays = 2;

//Message to be displayed on the LED matrix
String message = "A long time ago in a galaxy far, far away...";

//MD_MAX72XX display = MD_MAX72XX(MD_MAX72XX::GENERIC_HW, DATAPIN, CLKPIN, CSPIN, numDisplays);
MD_Parola parola = MD_Parola(MD_MAX72XX::GENERIC_HW, DATAPIN, CLKPIN, CSPIN, numDisplays);

// put function declarations here:
int myFunction(int, int);

void setup() {
  // put your setup code here, to run once:
  //display.begin();
  //display.clear();
  parola.begin();
  parola.displayScroll(message.c_str(), PA_CENTER, PA_SCROLL_LEFT, 100);
}

void loop() {
  // put your main code here, to run repeatedly:
  /* display.setChar(15, 'J');
  display.setChar(10, 'o');
  display.setChar(6, 'l');
  display.setChar(5, 'l');
  display.setChar(4, 'y');
  }*/

  
 if (parola.displayAnimate()){
  parola.displayReset();
 }

  
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}