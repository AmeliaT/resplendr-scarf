/*
Arduino example sketch for Resplendr Scarf, which utilizes a strip of 50 NeoPixels,
an Adafruit Gemma M0, and a tactile button to navigate modes. Use JST LiPoly or 
USB power bank. 

Full build information, build kits, and finished products available via www.resplendr.com
*/

//sketch setup information
#include <FastLED.h>  //  fastLED library

//LED information
#define NUM_LEDS    50      // adjust this to the number of LEDs you have
#define LED_TYPE    WS2812B // adjust this to the type of LEDS. This is for Neopixels
#define COLOR_ORDER GRB
#define BRIGHTNESS  255     // 0-255, 0 is dark, 255 is full brightness
#define SATURATION  255     // 0-255, 0 is pure white, 255 is fully saturated color
#define UPDATES_PER_SECOND 100

//confirm data & button pin information
#define DATA_PIN    1 //  adjust this to the pin you've connected your LEDs to   
#define BUTTON_PIN  2 //  Connect the button to GND and one of the pins.
#define NUM_MODES 10  //  Update this number to the highest number of "cases"


uint8_t gHue = 0;     // rotating "base color" used by many of the patterns
uint16_t STEPS = 30;  // STEPS set dynamically once we've started up
uint16_t SPEED = 30;  // SPEED set dynamically once we've started up

CRGB leds[NUM_LEDS];
CRGBPalette16 currentPalette;
TBlendType    currentBlending;

int ledMode = 0;

uint8_t colorLoop = 1;


//One way of making a palette of colors to animate
const TProgmemPalette16 SunsetColors_p PROGMEM =
{
  CRGB:: Crimson,
  CRGB:: Maroon,
  CRGB:: Red,
  CRGB:: OrangeRed,
 
  CRGB:: Crimson,
  CRGB:: Maroon,
  CRGB:: Red,
  CRGB:: OrangeRed,
 
  CRGB:: Crimson,
  CRGB:: Maroon,
  CRGB:: Red,
  CRGB:: OrangeRed,
 
  CRGB:: Crimson,
  CRGB:: Maroon,
  CRGB:: Red,
  CRGB:: OrangeRed,
};

//-----------------Button Setup------------
byte prevKeyState = HIGH;         // button is active low
unsigned long keyPrevMillis = 0; 
const unsigned long keySampleIntervalMs = 25; 
 

//------------------SETUP------------------
void setup() {
  delay( 2000 ); // power-up safety delay
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  LEDS.setBrightness(BRIGHTNESS);
 
  currentBlending = LINEARBLEND; //all of these will be blended unless I tell them not to
  //You may add: 
  //currentBlending = NOBLEND;
  //after the declared steps for each mode. All modes thereafter will follow suit. 
  //In order to reset to blend, add:
  //
  //currentBlending = LINEARBLEND;
  //to the next mode.

  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

//------------------MAIN LOOP------------------
void loop() {

 if (millis() - keyPrevMillis >= keySampleIntervalMs) {
        keyPrevMillis = millis();

        byte currKeyState = digitalRead(BUTTON_PIN);
        
        if ((prevKeyState == HIGH) && (currKeyState == LOW)) {
            KeyPress();
        }     
        prevKeyState = currKeyState;
    }

  static uint8_t startIndex = 0;
  startIndex = startIndex + 1; /* motion speed */

  switch (ledMode) {

//FastLED has a bunch of built-in "palettes" to choose from:
//RainbowColors_p   is all the colors of the rainbow
//PartyColors_p     is all the colors of the rainbow minus greens
//RainbowStripeColors_p is all the colors of the rainbow divided into stripes
//HeatColors_p      is reds and yellows, white, and black
//LavaColors_p      is more reds and orangey colors
//ForestColors_p    is greens and yellows
//OceanColors_p     is lots of blues and aqua colors
//CloudColors_p     is blues and white
//MyColors_p        is whatever you define above

//The group of colors in a palette are sent through a strip of LEDS in speed and step increments youve chosen
//You can change the SPEED and STEPS to make things look exactly how you want
//SPEED refers to how fast the colors move.  Higher numbers = faster motion
//STEPS refers to how wide the bands of color are. Based on the palette & number of LEDs, some look better at different steps

  case 0: {currentPalette = RainbowColors_p;  SPEED = 50; STEPS = 5;}  break;
  case 1: {currentPalette = RainbowStripeColors_p;  SPEED = 20; STEPS = 50;} break;
  case 2: {currentPalette = PartyColors_p;  SPEED = 5;  STEPS = 2;} break;

  case 3: {Red();} break;
  case 4: {currentPalette = LavaColors_p; SPEED = 200;  STEPS = 50;} break; 

  case 5: {currentPalette = SunsetColors_p; SPEED = 50;  STEPS = 5;} break;
  
  case 6: {Gold();} break;

  case 7: {currentPalette = ForestColors_p; SPEED = 50; STEPS = 5;} break;

  case 8: {currentPalette = OceanColors_p;  SPEED = 50;  STEPS = 50;} break;

  case 9: {Purple();} break;
  case 10: {GalaxyColors(); SPEED = 25; STEPS = 4;}  break; 
  } 

  FillLEDsFromPaletteColors(startIndex);
  FastLED.show();
  FastLED.delay(1000 / SPEED);  
}

void KeyPress() {
    ledMode++;
    if (ledMode > NUM_MODES){
    ledMode=0; }
}

void FillLEDsFromPaletteColors( uint8_t colorIndex) {
  for( int i = 0; i < NUM_LEDS; i++) {
    leds[i] = ColorFromPalette( currentPalette, colorIndex, BRIGHTNESS, currentBlending);
    colorIndex += STEPS;              
  }
}


void Red()
{
    fill_solid( currentPalette, 16, CRGB::Red);
}

void OrangeRed()
{
    fill_solid( currentPalette, 16, CRGB::OrangeRed);
}

void Gold()
{
    fill_solid( currentPalette, 16, CRGB::Gold);
}

void Green()
{
    fill_solid( currentPalette, 16, CRGB::Green);
}

void Purple()
{
    fill_solid( currentPalette, 16, CRGB::Purple);
}

void Blue()
{
    fill_solid( currentPalette, 16, CRGB::Blue);
}

void GalaxyColors()
{
    fill_solid( currentPalette, 16, CRGB::Black);
    // set half of the LEDs to the color selected here
    currentPalette[1] = CRGB::MidnightBlue;
    currentPalette[2] = CRGB::Indigo;
    currentPalette[5] = CRGB::Navy;
    currentPalette[6] = CRGB::Teal;
    currentPalette[9] = CRGB::MidnightBlue;
    currentPalette[10] = CRGB::Indigo;
    currentPalette[13] = CRGB::Navy;
    currentPalette[14] = CRGB::Teal;

}

void MermaidColors()
{
    CRGB DeepPink = CRGB(255,20,147);
    CRGB DarkBlue = CRGB   (0,0,139);
    CRGB Teal = CRGB(0,128,128);
    CRGB BlueViolet = CRGB   (138,43,226);
    CRGB DodgerBlue = CRGB   (30,144,255);
    CRGB Turquoise = CRGB   (0,206,209);
    CRGB Indigo = CRGB   (75,0,130);
    
    currentPalette = CRGBPalette16(
                                   DodgerBlue,  DarkBlue,  Teal,  Indigo,
                                   DodgerBlue,  DarkBlue,  Turquoise,  BlueViolet,
                                   DodgerBlue,  DarkBlue,  Teal,  BlueViolet,
                                  DodgerBlue,  DarkBlue,  Turquoise,  Indigo);
}
