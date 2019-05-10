// include the library code:
#include <LiquidCrystal.h>
#include "DHT.h"
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SPI.h>

// set the DHT Pin
#define DHTPIN 6

// For the breakout, you can use any 2 or 3 pins
// These pins will also work for the 1.8" TFT shield
#define TFT_CS     10
#define TFT_RST    0  // you can also connect this to the Arduino reset
// in which case, set this #define pin to -1!
#define TFT_DC     8

// Option 1 (recommended): must use the hardware SPI pins
// (for UNO thats sclk = 13 and sid = 11) and pin 10 must be
// an output. This is much faster - also required if you want
// to use the microSD card (see the image drawing example)
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

// Option 2: use any pins but a little slower!
#define TFT_SCLK 13   // set these to be whatever pins you like!
#define TFT_MOSI 11   // set these to be whatever pins you like!
//Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);


float p = 3.1415926;

// initialize the library with the numbers of the interface pins
//LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

void setup() {
	Serial.begin(9600);
	Serial.print("Temp and Humidity sensor");
	// Use this initializer if you're using a 1.8" TFT
	tft.initR(INITR_BLACKTAB);   // initialize a ST7735S chip, black tab

	// set up the LCD's number of columns and rows: 
	//lcd.begin(16, 2);
	dht.begin();
	// headings
	tft.fillScreen(ST7735_BLACK);
	tft.setRotation(1);
	testdrawtext("Sensor 1", ST7735_WHITE);
	testdrawtext("Temp:  Humidity:", ST7735_WHITE);
	// Print a message to the LCD.
	//lcd.print("Temp:  Humidity:");
}

void loop() {
	delay(500);
	// set the cursor to column 0, line 1
	// (note: line 1 is the second row, since counting begins with 0):
	//lcd.setCursor(0, 1);
	// read humidity
	float h = dht.readHumidity();
	//read temperature in Fahrenheit
	float f = dht.readTemperature(true);

	if (isnan(h) || isnan(f)) {
		//lcd.print("ERROR");
		return;
	}

	//lcd.print(f);
	//lcd.setCursor(7, 1);
	//lcd.print(h);
}

void testdrawtext(char *text, uint16_t color) {
	tft.setCursor(0, 0);
	tft.setTextColor(color);
	tft.setTextWrap(true);
	tft.print(text);
}