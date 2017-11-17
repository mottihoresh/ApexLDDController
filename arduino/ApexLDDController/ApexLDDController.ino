#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


#define channel1 0
#define channel2 1

Adafruit_SSD1306 display(4);
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

struct LedPuck {
  byte uv;  // UV Channel
  byte rb;  // Royal Blue Channel
  byte b;   // Blue Channel
  byte w;   // Cool White Channel
  byte g;   // Green Channel
  byte r;   // Red Channel
};


// Light presets.
#define numberOfPresets 10
const LedPuck lightPresets[] = {
  {17,17,17,37,100,100},      // 5K
  {68,68,68,87,100,100},      // 7K
  {87,87,87,100,100,100},     // 10K
  {100,100,100,100,100,100},  // 12K
  {100,100,100,45,45,45},     // 14K
  {100,100,100,25,25,25},     // 18K
  {100,100,100,17,17,17},     // 20K
  {50,100,0,0,0,45},          // POLYP FLUORESCNESE
  {100,100,100,10,15,35},     // CORAL RADIANCE
  {100,100,100,0,0,50}        // REEF CREATIONS
};

const String PresetNames[] = {
  "5K",
  "7K",
  "10K",
  "12K",
  "14K",
  "18K",
  "20K",
  "PF",
  "CR",
  "RC"
};


// Maps the pins for each puck.
const LedPuck channelConfigurations[] = {
  //{uv,rb,b,w,g,r}
  {0,1,2,3,4,5}, // Channel 1
  {6,7,8,9,10,11}  // Challen 2
};


int channel1Color = A0;
int channel1Intensity = A1;
int channel2Color = A2;
int channel2Intensity = A3;

int scl = A5;
int sda = A4;

void setup() {
  setupPwmChannels();
  setupDisplay();
}


void loop() {

  delay(1);        

  displayLoop();
  lightsLoop();

}
