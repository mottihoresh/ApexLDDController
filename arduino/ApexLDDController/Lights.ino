void setupPwmChannels() {
	  // put your setup code here, to run once:
  pwm.begin();
  pwm.setPWMFreq(1600);  // This is the maximum PWM frequency

  // save I2C bitrate
  uint8_t twbrbackup = TWBR;
  // must be changed after calling Wire.begin() (inside pwm.begin())
  TWBR = 12; // upgrade to 400KHz!
}

int getChannelValue(int channel) {

	// Get input and avrage it out.
	int total = 0; 	
	int avg = 0;
	int count = 0;
	while (count < 10) {
		total += analogRead(channel);
		count++;
	}

	avg = total / 10;

	return map(avg, 10, 920, 0, 4095);
}

int getChannelPrecentage(int channelValue) {
	return map(channelValue, 0, 4095, 0, 100);
}


int getIntensityLevel(int intensityLevelChannel) {
	int channelValue = getChannelValue(intensityLevelChannel);
	return getChannelPrecentage(channelValue);
}

int getColorIndex(int colorChannel){
	int channelValue = getChannelValue(colorChannel);
	return map(channelValue, 0, 4095, 0, numberOfPresets-1);
}

struct LedPuck getColorMapping(int channelValue) {
	int colorIndex = getColorIndex(channelValue);
	return lightPresets[colorIndex];
}

void setColorChannel(int pin, int intensity) {
	pwm.setPWM(pin, 0, intensity);
}

void updateFixture(int fixtureIndex, int colorChannel, int intensityChannel) {
	int intensityLevel = getIntensityLevel(intensityChannel);
	LedPuck colorMapping = getColorMapping(colorChannel);
	LedPuck ledPinout = channelConfigurations[fixtureIndex];

	setColorChannel(ledPinout.uv, colorMapping.uv * (intensityLevel / 100));
	setColorChannel(ledPinout.rb, colorMapping.rb * (intensityLevel / 100));
	setColorChannel(ledPinout.b, colorMapping.b * (intensityLevel / 100));
	setColorChannel(ledPinout.w, colorMapping.w * (intensityLevel / 100));
	setColorChannel(ledPinout.g, colorMapping.g * (intensityLevel / 100));
	setColorChannel(ledPinout.r, colorMapping.r * (intensityLevel / 100));
}

void lightsLoop() {
	updateFixture(0, channel1Color, channel1Intensity);
	updateFixture(1, channel2Color, channel2Intensity);
}

