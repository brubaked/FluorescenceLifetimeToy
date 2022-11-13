// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// Released under the GPLv3 license to match the rest of the
// Adafruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN        3 // On Trinket or Gemma, suggest changing this to 1

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 2 // Popular NeoPixel ring size

// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 50 // Time (in milliseconds) to pause between pixels


int count = 0;
int ButtonPin = 13;
int ButtonState = 1;
unsigned long startTime;
unsigned long currentTime = 0;
float TDPeriod = 1000;
float halfLife = TDPeriod/8;
float rhBrightness;
float LEDBrightness;

void setup() {
  Serial.begin(9600); // open the serial port at 9600 bps:
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  pinMode(ButtonPin, INPUT);
}

void loop() {
  
  if (ButtonState == -1){ //Time domain section
    
    startTime = millis();
    currentTime = millis();
    
    delay(1);

    while (currentTime - startTime < TDPeriod){ //LED On
      currentTime = millis();
      pixels.setPixelColor(0, pixels.Color(0, 0, 150));
      delay(halfLife/6);
      rhBrightness = (1 - (pow(2.718, (-((currentTime - startTime)/halfLife)))))*255;
      // Serial.println(rhBrightness);
      pixels.setPixelColor(1, pixels.Color(rhBrightness*0.25, rhBrightness*0.75, 0));
      pixels.show();
      if (digitalRead(ButtonPin) == 1){
        ButtonState = ButtonState * (-1);
        pixels.clear();
        pixels.show();
        Serial.println(ButtonState);
        startTime = 0;
        delay(500);
      }
    }
    while (currentTime - startTime < (TDPeriod * 2)){ //LED Off
      currentTime = millis();
      pixels.setPixelColor(0, pixels.Color(0, 0, 0));
      rhBrightness = ((pow(2.718, (-((currentTime - TDPeriod - startTime)/halfLife)))))*255;
      // Serial.println(rhBrightness);
      pixels.setPixelColor(1, pixels.Color(rhBrightness*0.25, rhBrightness*0.75, 0));
      pixels.show();
      if (digitalRead(ButtonPin) == 1){
        ButtonState = ButtonState * (-1);
        pixels.clear();
        pixels.show();
        Serial.println(ButtonState);
        startTime = 0;
        delay(500);
      }
    }
  }  
  if (ButtonState == 1){ //Frequency domain section
    
    startTime = millis();
    currentTime = millis();
    
    delay(5);

    while (ButtonState == 1){ 
      currentTime = millis();
      // Serial.println(currentTime - startTime);
      LEDBrightness = ((sin((currentTime - startTime - halfLife)/200) * 0.4) + 0.6) * 255;
      // Serial.println(LEDBrightness);
      pixels.setPixelColor(0, pixels.Color(0, 0, LEDBrightness));
      rhBrightness = ((sin((currentTime - startTime - halfLife*3)/200) * 0.4) + 0.6) * 255;
      // Serial.println(rhBrightness);
      pixels.setPixelColor(1, pixels.Color(rhBrightness*0.25, rhBrightness*0.75, 0));
      pixels.show();
      if (digitalRead(ButtonPin) == 1){
        ButtonState = ButtonState * (-1);
        pixels.clear();
        pixels.show();
        Serial.println(ButtonState);
        startTime = 0;
        delay(500);
      }
    } 
  }
    
  if (digitalRead(ButtonPin) == 1){
    ButtonState = ButtonState * (-1);
    // pixels.setPixelColor(0, pixels.Color(0, 0, 0));
    // pixels.setPixelColor(1, pixels.Color(0, 0, 0));
    pixels.show();
    Serial.println(ButtonState);
    startTime = millis();
    // Serial.println(startTime);
    // Serial.println(currentTime);
    delay(500);
  }

    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
    // Here we're using a moderately bright green color:
    // pixels.setPixelColor(0, pixels.Color(0, 20, 0));
    // pixels.setPixelColor(1, pixels.Color(0, 20, 0));
    // Serial.print("Red");

    // pixels.show();   // Send the updated pixel colors to the hardware.

    // pixels.clear(); // Set all pixel colors to 'off'
}
