#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


#define channel1 0
#define channel2 1

struct LedPuck {
  byte uv;  // UV Channel
  byte rb;  // Royal Blue Channel
  byte b;   // Blue Channel
  byte w;   // Cool White Channel
  byte g;   // Green Channel
  byte r;   // Red Channel
};

#define numberOfPresets 10
// Light presets.
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


// Maps the pins for each puck.
const LedPuck channelConfigurations[] = {
  //{uv,rb,b,w,g,r}
  {0,1,2,3,4,5}, // Channel 1
  {6,7,8,9,10,11}  // Challen 2
};


Adafruit_SSD1306 display(4);

int channel1Color = A0;
int channel1Intensity = A1;
int channel2Color = A2;
int channel2Intensity = A3;

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

int scl = A5;
int sda = A4;

const int numReadings = 10;

int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int average = 0;                // the average

int tmpValue = 0;


void setup() {
  // put your setup code here, to run once:
  pwm.begin();
  pwm.setPWMFreq(1600);  // This is the maximum PWM frequency

  // Set up display
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  delay(2000);

  // Clear the buffer.  
  display.clearDisplay();

    // draw a single pixel
    display.drawPixel(10, 10, WHITE);
  // Show the display buffer on the hardware.
  // NOTE: You _must_ call display after making any drawing commands
  // to make them visible on the display hardware!
  display.display();
  delay(2000);
  display.clearDisplay();
  

  // save I2C bitrate
  uint8_t twbrbackup = TWBR;
  // must be changed after calling Wire.begin() (inside pwm.begin())
  TWBR = 12; // upgrade to 400KHz!
  
  // initialize all the readings to 0:
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
}

int getReading(int inputPin) {


 readIndex = 0;              // the index of the current reading
 total = 0;                  // the running total
 average = 0;                // the average

 tmpValue = 0;
   // put your main code here, to run repeatedly:

   // subtract the last reading:
   total = total - readings[readIndex];
  // read from the sensor:
  readings[readIndex] = analogRead(inputPin);
  // add the reading to the total:
  total = total + readings[readIndex];
  // advance to the next position in the array:
  readIndex = readIndex + 1;

  // if we're at the end of the array...
  if (readIndex >= numReadings) {
    // ...wrap around to the beginning:
    readIndex = 0;
  }

  // calculate the average:
  return (total / numReadings);
  // send it to the computer as ASCII digits
}
void loop() {

  int i = 540;
  i = map(i, 1023, 0, 100, 0);


 
  
  tmpValue = map(average, 130, 1023, 0, 4096);
//  pwm.setPWM(0, 0, tmpValue );
  delay(1);        // delay in between reads for stability



  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE, BLACK);
  display.setCursor(0,0);
  display.println("LDD Convertor Test");
  display.setCursor(0,9);
  display.print("Channel 1:   ");
    display.print(analogRead(channel1Color));

//  display.print(getReading(channel1Color));
  display.println("%");
  display.print("Channel 2:   ");
    display.print(analogRead(channel1Intensity));

//    display.print(getReading(channel1Intensity));
  display.println("%");
  display.print("Channel 3:   ");
    display.print(analogRead(channel2Color));

//    display.print(getReading(channel2Color));
  display.println("%");
  display.print("Channel 4:   ");
  display.print(getChannelPrecentage(analogRead(channel2Intensity)));
//    display.print(getReading(channel2Intensity));
  display.println("%");
  display.display();

  
// Set 1
  pwm.setPWM(0, 0, 0 );       // Channel 1 (Red) 
  pwm.setPWM(1, 0, 0 );       // Channel 2 (Royal Blue or some other blue....)
  pwm.setPWM(2, 0, 0 );      // Channel 3 (Maybe Royal Blue again...)
  pwm.setPWM(3, 0, 1000 );      // Channel 4 (Cool white)
  pwm.setPWM(4, 0, 4095 );      // Channel 5 (UV or maybe indigo)
  pwm.setPWM(5, 0, 0 );      // Green

   // Set 2
   pwm.setPWM(6, 0, 0 );
  pwm.setPWM(7, 0, 0 ); // not working
  pwm.setPWM(8, 0, 0 );  // Channel 1
  pwm.setPWM(9, 0, 1000 ); // Channel 2
  pwm.setPWM(10, 0, 4095 ); // Channel 3
  pwm.setPWM(11, 0, 0 ); 
  
  pwm.setPWM(12, 0, 4096 );
  pwm.setPWM(13, 0, 4096 );
  pwm.setPWM(14, 0, 4096 );
  pwm.setPWM(15, 0, 4096 );


}
