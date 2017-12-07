/*
  Copyright (c) 2014-2016 NicoHood
  See the readme for credit to other people.

  MSGEQ7 FastLED example
  Output via Led strip and FastLED library

  Reads MSGEQ7 IC with 7 different frequencies from range 0-255
  63Hz, 160Hz, 400Hz, 1kHz, 2.5kHz, 6.25KHz, 16kHz

*/

// FastLED
#include "FastLED.h"

#define LED_PINS    6  //MOSI, SCK // DATA_PIN, or DATA_PIN, CLOCK_PIN
#define COLOR_ORDER GRB
#define CHIPSET     WS2812 // WS2811 LPD8806
#define NUM_LEDS    34

#define BRIGHTNESS  255  // reduce power consumption
#define LED_DITHER  255  // try 0 to disable flickering
#define CORRECTION  TypicalLEDStrip

CRGB leds[NUM_LEDS]; // Define the array of leds

// MSGEQ7
#include "MSGEQ7.h"
#define pinAnalogLeft A7

#define pinReset 3
#define pinStrobe 2
#define MSGEQ7_INTERVAL ReadsPerSecond(50)
#define MSGEQ7_SMOOTH true

int buttonPin = 9;

CMSGEQ7<MSGEQ7_SMOOTH, pinReset, pinStrobe, pinAnalogLeft> MSGEQ7;

int treeRight[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
int treeRightSize = sizeof(treeRight) / sizeof(int);;
int star[] = {13, 14, 15, 16, 17};
int starSize = sizeof(star) / sizeof(int);
int treeLeft[] = {18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28};
int treeLeftSize = sizeof(treeLeft) / sizeof(int);
int middle[] = {12, 29, 30, 31, 32, 33, 34};
int middleSize = sizeof(middle) / sizeof(int);
int tree[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28};
int treeSize = sizeof(tree) / sizeof(int);
int all[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34};
int allSize = sizeof(all) / sizeof(int);

long animationTimerTimeStamp = 0;
long animationTimerValue = 50;

boolean doAnimation = false;

long tick = 0;

void setup() {
  Serial.begin(9600);

  pinMode(buttonPin, INPUT_PULLUP);

  // FastLED setup
  FastLED.addLeds<CHIPSET, LED_PINS, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(CORRECTION);
  FastLED.setBrightness( BRIGHTNESS );
  FastLED.setDither(LED_DITHER);
  FastLED.show(); // needed to reset leds to zero

  // This will set the IC ready for reading
  MSGEQ7.begin();


}

void loop() {

  if (digitalRead(buttonPin) == LOW) {
    bool newReading = MSGEQ7.read(MSGEQ7_INTERVAL);
    if (newReading) {
      doSound();
    }
  } else {
    if (animationTimer() == true) {
      Serial.println(millis());
      doAnimatition();
      tick++;
    }
  }

  FastLED.show();

}



boolean animationTimer() {
  if ( (millis() - animationTimerTimeStamp) > animationTimerValue) {
    animationTimerTimeStamp = millis();
    return true;
  }
  return false;
}

void doSound() {
  // visualize the average bass of both channels
  uint8_t val = MSGEQ7.get(MSGEQ7_BASS);
  // Reduce noise
  val = mapNoise(val);
  // Visualize leds to the beat
  CRGB color = CRGB::White;
  color.nscale8_video(val);
  //fill_solid(leds, NUM_LEDS, color);
  for ( int i = 0; i < allSize; i++) {
    leds[all[i]] = color;
  }
}

void doAnimatition() {
  starAnimation();
  treeAnimation();
  middleAnimation();
}

void starAnimation() {
  int pointer = tick % starSize;
  // Serial.println(pointer);
  for (int i = 0; i < starSize; i++) {
    leds[star[i]] = CRGB::Black;
  }
  leds[star[pointer]] = CRGB::Yellow;
}

boolean treeFoward = true;

void treeAnimation() {
  int pointer = tick % treeSize;
  for (int i = 0; i < treeSize; i++) {
    leds[tree[i]] = CRGB::Green;
  }
  leds[tree[pointer]] = CRGB::Red;
}

void middleAnimation() {
  int pointer = tick % middleSize;
  for (int i = 0; i < middleSize; i++) {
    leds[middle[i]] = CRGB::Blue;
  }
  leds[middle[pointer]] = CRGB::Purple;

}



