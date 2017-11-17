int getChannelValue(int channel) {

	// Get input and avrage it out.
	int total = 0; 	int avg = 0;
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


int getIntensityLevel(int channelValue) {
  return getChannelPrecentage(channelValue);
}

int getColorIndex(int channelValue){
  return map(channelValue, 0, 4095, 0, numberOfPresets-1);
}

struct LedPuck getColorMapping(int channelValue) {

  int colorIndex = getColorIndex(channelValue);
  return lightPresets[colorIndex];
}

