void setupDisplay() {
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
}

void displayLoop() {
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
}
