#include <FastLED.h>

#define LED_PIN     5
#define NUM_LEDS    600
#define BRIGHTNESS  80
#define LED_TYPE    WS2812
#define COLOR_ORDER GRB

#define NUM_EFFECTS 2

CRGB leds[NUM_LEDS];

#define UPDATES_PER_SECOND 120


CRGBPalette16 currentPalette;
TBlendType    currentBlending;

extern CRGBPalette16 myRedWhiteBluePalette;
extern const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM;

byte animation = 0;

void setup() {
  delay( 1000 ); // power-up safety delay
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(  BRIGHTNESS );

  loadEffect(0);
}


unsigned long lastChk = 0;
byte currentEffect = 0;

void loop()
{
  if(millis() - lastChk > 5 * 60 * 1000) {
    lastChk = millis();

    currentEffect++;

    if(currentEffect >= NUM_EFFECTS) {
      currentEffect = 0;
    }
    
    loadEffect(currentEffect);  
  }
  

  static uint8_t startIndex = 0;
  startIndex = startIndex + 1; /* motion speed */

  switch (animation) {
    case 0:
      animateFillLEDsFromPaletteColors( startIndex);
      break;
    case 1:
      animateCylon( startIndex);
      break;
  }


  FastLED.show();
  FastLED.delay(1000 / UPDATES_PER_SECOND);
}

byte incAmount;

void animateCylon(uint8_t colorIndex) {
  uint8_t brightness = 128;

  for (int whiteLed = 0; whiteLed < NUM_LEDS; whiteLed = whiteLed + 1) {
     leds[whiteLed] = ColorFromPalette( currentPalette, whiteLed % 255, inoise8((whiteLed*10) + colorIndex*10), currentBlending);
  }

  FastLED.show();
}

void animateFillLEDsFromPaletteColors( uint8_t colorIndex)
{
  uint8_t brightness = 255;


  for ( int i = 0; i < NUM_LEDS; i++) {
    colorIndex += incAmount;
    if (colorIndex > 255) {
      //colorIndex = 0;
    }

    leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);

  }
}


void loadEffect(byte effect)
{
  switch(effect) {
      case 0:
        SetupSovietGearsRed();
        break;
      case 1:
        SetupSovietYellowFire();
        break;
      case 2:
        SetupSovietFire();
        break;
    }
}

void SetupSovietCylon() {

  currentPalette = LavaColors_p;
  currentPalette[0] = CRGB(0, 0, 0);

  currentBlending = LINEARBLEND;
  animation = 1;
  incAmount = 1;

  for (int whiteLed = 0; whiteLed < NUM_LEDS; whiteLed = whiteLed + 1) {
    leds[whiteLed] = ColorFromPalette( currentPalette, 0, 255, currentBlending);
  }
}

void SetupSovietGears()
{
  // 'black out' all 16 palette entries...
  fill_solid( currentPalette, 16, CRGB::Black);
  // and set every fourth one to white.
  currentPalette[0] = CRGB(255, 0, 0);
  currentPalette[1] = CRGB(255, 0, 0);
  currentPalette[2] = CRGB(32, 0, 0);
  currentPalette[3] = CRGB(32, 0, 0);

  currentPalette[4] = CRGB(0, 0, 0);
  currentPalette[5] = CRGB(0, 0, 0);
  currentPalette[6] = CRGB(100, 100, 100);
  currentPalette[7] = CRGB(32, 0, 0);

  currentPalette[8] = CRGB(255, 0, 0);
  currentPalette[9] = CRGB(255, 0, 0);
  currentPalette[10] = CRGB(32, 0, 0);
  currentPalette[11] = CRGB(32, 0, 0);

  currentPalette[12] = CRGB(0, 0, 0);
  currentPalette[13] = CRGB(0, 0, 0);
  currentPalette[14] = CRGB(0, 0, 0);
  currentPalette[15] = CRGB(0, 0, 0);

  currentBlending = LINEARBLEND;

  incAmount = 10;
  animation = 0;
}

void SetupSovietGearsRed()
{
  // 'black out' all 16 palette entries...
  fill_solid( currentPalette, 16, CRGB::Black);
  // and set every fourth one to white.
  currentPalette[0] = CRGB(255, 0, 0);
  currentPalette[1] = CRGB(255, 0, 0);
  currentPalette[2] = CRGB(32, 0, 0);
  currentPalette[3] = CRGB(32, 0, 0);

  currentPalette[8] = CRGB(255, 0, 0);
  currentPalette[9] = CRGB(255, 0, 0);
  currentPalette[10] = CRGB(32, 0, 0);
  currentPalette[11] = CRGB(32, 0, 0);

  currentBlending = LINEARBLEND;

  incAmount = 10;
  animation = 0;
}

void SetupSovietYellowFire()
{
  // 'black out' all 16 palette entries...
  fill_solid( currentPalette, 16, CRGB::Black);
  // and set every fourth one to white.
  currentPalette[0] = CRGB(255, 0, 0);
  currentPalette[1] = CRGB(30, 0, 0);
  currentPalette[2] = CRGB(255, 0, 0);
  currentPalette[3] = CRGB(128, 0, 0);
  currentPalette[4] = CRGB(96, 0, 0);
  currentPalette[5] = CRGB(164, 0, 0);

  currentPalette[6] = CRGB(255, 150, 0);
  currentPalette[7] = CRGB(255, 140, 10);
  currentPalette[8] = CRGB(255, 178, 0);
  currentPalette[9] = CRGB(30, 30, 0);
  currentPalette[9] = CRGB(255, 166, 20);

  currentPalette[11] = CRGB(255, 0, 0);
  currentPalette[12] = CRGB(64, 0, 0);
  currentPalette[13] = CRGB(255, 0, 0);
  currentPalette[14] = CRGB(60, 0, 0);

  currentPalette[15] = CRGB(90, 30, 0);

  currentBlending = LINEARBLEND;

  incAmount = 2;
  animation = 0;
}

void SetupSovietFire()
{
  // 'black out' all 16 palette entries...
  fill_solid( currentPalette, 16, CRGB::Black);
  // and set every fourth one to white.
  currentPalette[0] = CRGB(255, 0, 0);
  currentPalette[1] = CRGB(64, 0, 0);
  currentPalette[2] = CRGB(255, 0, 0);
  currentPalette[3] = CRGB(128, 0, 0);
  currentPalette[4] = CRGB(96, 0, 0);
  currentPalette[5] = CRGB(164, 0, 0);

  currentPalette[6] = CRGB(255, 255, 0);
  currentPalette[7] = CRGB(64, 64, 0);
  currentPalette[8] = CRGB(255, 255, 0);
  currentPalette[9] = CRGB(128, 128, 0);


  currentBlending = LINEARBLEND;

  incAmount = 2;
  animation = 0;
}

