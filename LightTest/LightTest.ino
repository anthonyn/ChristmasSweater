// Use if you want to force the software SPI subsystem to be used for some reason (generally, you don't)
// #define FASTLED_FORCE_SOFTWARE_SPI
// Use if you want to force non-accelerated pin access (hint: you really don't, it breaks lots of things)
// #define FASTLED_FORCE_SOFTWARE_SPI
// #define FASTLED_FORCE_SOFTWARE_PINS
#include "FastLED.h"

///////////////////////////////////////////////////////////////////////////////////////////
//
// Move a white dot along the strip of leds.  This program simply shows how to configure the leds,
// and then how to turn a single pixel white and then off, moving down the line of pixels.
//

// How many leds are in the strip?
#define NUM_LEDS 34

// Data pin that led data will be written out over
#define DATA_PIN 6

// Clock pin only needed for SPI based chipsets when not using hardware SPI
//#define CLOCK_PIN 8

// This is an array of leds.  One item for each led in your strip.
CRGB leds[NUM_LEDS];

int treeRight[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
int treeRightSize = sizeof(treeRight) / sizeof(int);;
int star[] = {13, 14, 15, 16, 17};
int starSize = sizeof(star) / sizeof(int);
int treeLeft[] = {18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28};
int treeLeftSize = sizeof(treeLeft) / sizeof(int);
int middle[] = {12, 29, 30, 31, 32, 33, 34};
int middleSize = sizeof(middle) / sizeof(int);
int tree = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28};
int treeSize = sizeof(tree) / sizeof(int);

// This function sets up the ledsand tells the controller about them
void setup() {
  Serial.begin(9600);
  // sanity check delay - allows reprogramming if accidently blowing power w/leds
  delay(2000);

  FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);

  Serial.print("TreeRigthSize is: ");
  Serial.println(treeRightSize);
  for ( int i = 0; i < treeRightSize; i++) {
    leds[treeRight[i]] = CRGB::Red;
    Serial.print(treeRight[i]);
  }
  Serial.print("starSize is: ");
  Serial.println(starSize);
  for ( int i = 0; i < starSize; i++) {
    leds[star[i]] = CRGB::White;
    Serial.print(star[i]);
  }
  for ( int i = 0; i < treeLeftSize; i++) {
    leds[treeLeft[i]] = CRGB::Blue;
  }
  for ( int i = 0; i < middleSize; i++) {
    leds[middle[i]] = CRGB::Green;
  }
  FastLED.show();

}

// This function runs over and over, and is where you do the magic to light
// your leds.
void loop() {
  // Move a single white led
  //  for (int whiteLed = 0; whiteLed < NUM_LEDS; whiteLed = whiteLed + 1) {
  //    // Turn our current led on to white, then show the leds
  //    leds[whiteLed] = CRGB::White;
  //
  //    // Show the leds (only one of which is set to white, from above)
  //    FastLED.show();
  //
  //    // Wait a little bit
  //    delay(100);
  //
  //    // Turn our current led back to black for the next loop around
  //    leds[whiteLed] = CRGB::Black;
  //  }
}

void 
