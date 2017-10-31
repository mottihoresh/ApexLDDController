#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

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

int inputPin = A0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pwm.begin();
  pwm.setPWMFreq(1600);  // This is the maximum PWM frequency

  // save I2C bitrate
  uint8_t twbrbackup = TWBR;
  // must be changed after calling Wire.begin() (inside pwm.begin())
  TWBR = 12; // upgrade to 400KHz!
  
  // initialize all the readings to 0:
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
}

void loop() {
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
  average = total / numReadings;
  // send it to the computer as ASCII digits
  
  tmpValue = map(average, 130, 1023, 0, 4096);
  Serial.println(average);
//  pwm.setPWM(0, 0, tmpValue );
  delay(1);        // delay in between reads for stability

// Set 1
  pwm.setPWM(0, 0, 4096 );       // Channel 1 (Red) 
  pwm.setPWM(1, 0, 4096 );       // Channel 2 (Royal Blue or some other blue....)
  pwm.setPWM(2, 0, 4096 );      // Channel 3 (Maybe Royal Blue again...)
  pwm.setPWM(3, 0, 4096 );      // Channel 4 (Cool white)
  pwm.setPWM(4, 0, 4096 );      // Channel 5 (UV or maybe indigo)
  pwm.setPWM(5, 0, 4096 );      // Green

   // Set 2
  pwm.setPWM(6, 0, 4096 );
  pwm.setPWM(7, 0, 4096 ); // not working
  pwm.setPWM(8, 0, 4096 );  // Channel 1
  pwm.setPWM(9, 0, 4096 ); // Channel 2
  pwm.setPWM(10, 0, 4096 ); // Channel 3
  pwm.setPWM(11, 0, 4096 ); 
  
  pwm.setPWM(12, 0, 4096 );
  pwm.setPWM(13, 0, 4096 );
  pwm.setPWM(14, 0, 4096 );
  pwm.setPWM(15, 0, 4096 );



    pwm.setPWM(10, 0, 4096 );
    delay(100);
      pwm.setPWM(10, 0, 4095 );
      delay(100);
}
