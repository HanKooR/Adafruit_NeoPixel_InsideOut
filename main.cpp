//THIS FILE IS WRITTEN FOR TEENSY3.2 on AtomIO/PlatformIO
//Adapt includes and pins when needed!

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.


#include <Arduino.h>
#include <Adafruit_NeoPixel.h>  //can be found here https://github.com/adafruit/Adafruit_NeoPixel
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 6               //pin of your digital out to led strip
#define NUMBER_OF_PIXELS 96 //this scatch needs an EVEN number of pixels!
#define BRIGHTNESS 128       //possible from 0-255

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMBER_OF_PIXELS, PIN, NEO_GRB + NEO_KHZ800);



void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  // End of trinket special code

  //set brightness from const above
  strip.setBrightness(BRIGHTNESS);

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void insideOut(uint8_t wait){
  uint32_t colorOne = strip.Color(255,0,0); //Red
  uint32_t colorTwo = strip.Color(0,255,0); //Green
  uint8_t middle = (NUMBER_OF_PIXELS/2);
  for(int o = 0; o < middle; o++){
    //color switching...
    uint32_t colorTemp = colorOne;
    colorOne = colorTwo;
    colorTwo = colorTemp;
    //from middle to outer borders
    for(int i = 0; i < middle-o; i++){
      strip.setPixelColor(middle+i, colorOne);
      strip.setPixelColor(middle-(i+1), colorTwo);
      strip.show();
      delay(wait);
      strip.setPixelColor(middle+i, 0, 0, 0);
      strip.setPixelColor(middle-(i+1), 0, 0, 0);
      strip.show();
      delay(wait);
    }
    //from outer borders back to the middle
    for(int i = 0; i < middle-o; i++){
      strip.setPixelColor((NUMBER_OF_PIXELS)-(i+o+1), colorOne);
      strip.setPixelColor(0+o+i, colorTwo);
      strip.show();
      delay(wait);
      strip.setPixelColor((NUMBER_OF_PIXELS)-(i+o+1), 0, 0, 0);
      strip.setPixelColor(0+o+i, 0, 0, 0);
      strip.show();
      delay(wait);
    }
  }

}

void loop() {
  insideOut(5); //takes an arg [uint8_t] for wait in ms between led switching
}
