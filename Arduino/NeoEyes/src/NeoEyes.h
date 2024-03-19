/*
  NeoEyes.h - Library for turning an 8x16 or two 8x8 NeoPixel matrix into a pair of expressive eyes
  Created by Sean Buchmeier +++, December 2023.
  License blah goes here
 */
#ifndef NeoEyes_h
#define NeoEyes_h

#include <Arduino.h>
#include <FastLED.h>

#define _NLEDS 128

enum emote {
  neutral,
  right,
  left,
  up,
  down,
  happy,
  sad,
  angry,
  confused,
  dead
};




class cNeoEyes
{
  public:
    //NeoEyes(int ledPin, int rightPin, bool kMatrixSerpentineLayout, bool kMatrixVertical);
    //NeoEyes(uint8_t  ledPin, uint8_t  rightPin = -1, bool kMatrixSerpentineLayout = true, bool kMatrixVertical = false);
    cNeoEyes(CRGB* ledPtr, uint16_t nLeds, bool kMatrixSerpentineLayout = true, bool kMatrixVertical = false);
    //NeoEyes(int ledPin, ESPIChipsets chipSet, EOrder rgbOrder, int rightPin, bool kMatrixSerpentineLayout, bool kMatrixVertical);
    //NeoEyes(int leftPin, int rightPin, ESPIChipsets chipSet, EOrder rgbOrder, bool kMatrixSerpentineLayout = true, bool kMatrixVertical = false);
    //void begin(uint8_t  ledPin);
    void begin(CLEDController& ctrl);
    void setEmote(emote expression);
    void setExpression(CRGB expression[8][16]);
    void setPinPositions(bool kMatrixSerpentineLayout = true, bool kMatrixVertical = false);
    uint16_t XY( uint8_t x, uint8_t y, bool _kMatrixSerpentineLayout = true, bool _kMatrixVertical = false);
    //CRGB _leds[_nLeds];
  private:
    bool _isSeparate = false;
    // 8x16, or 8x8 connected data out to data in of second 8x8
    //static const int _nLeds = 128;
    const int _kMatrixHeight = 8;
    const int _kMatrixWidth = 16;

    CRGB* const _leds;          ///< Pointer to LED data, in CRGB array
    const uint16_t maxLEDs;    ///< Number of RGB LEDs in the CRGB array
    uint16_t numLEDs;          ///< Number of RGB LEDs in the current strip
    CLEDController* controller = nullptr;  ///< Pointer to controller object for latching LED data


    // This matrix has the pin position associated with each visual
    // array location point
    int pinPositions[8][16] = {
      // Row 1
      { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 },
      // Row 2
      { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 },
      // Row 3
      { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 },
      // Row 4
      { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 },
      // Row 5
      { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 },
      // Row 6
      { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 },
      // Row 7
      { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 },
      // Row 8
      { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 }
    };
};

/**
* @brief FastLED implementation of the Adafruit_NeoPixel class for WS2812B strips, with data
*
* This is templated for a few reasons:
* * It allows the user to create a FastLED_NeoPixel class with (almost) the
*   same syntax as Adafruit_NeoPixel (using template args instead of function arguments):
*       
*       Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
*       FastLED_NeoPixel<LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800> strip;
* 
*   For ease of use this is preferable to splitting the arguments (`LED_COUNT`) 
*   between template and function.
* 
* * It allows allocating a static CRGB array for the LED data, so we don't have
*   to use heap allocation with `new()`
* * It allows us to create a begin() function that calls FastLED.addLeds
*   "automatically" without any other input or arguments. Just like
*   Adafruit_NeoPixel!
* 
* The one downside is that this splits the FastLED_NeoPixel and
* FastLED_NeoPixel_Variant classes, so static calls to FastLED_NeoPixel will
* fail for lack of template arguments. But that's how the cookie crumbles.
* 
* @tparam NumLeds the number of LEDs in the strip
* @tparam DataPin the number for the data pin connected to the strip
* @tparam RgbOrder the RGB channel order for the strips, either as a NeoPixel
*         define (e.g. NEO_GRB) or a FastLED EOrder enum value (e.g. GRB). By
*         default this is GRB, which is the typical color order for most
*         NeoPixel (WS2812B) strips.
* 
* @see Adafruit_NeoPixel
* @see NewFuncs
* @see Unimplemented
*/
template<uint8_t DataPin>
class NeoEyes : public cNeoEyes {
public:
	NeoEyes() : cNeoEyes(ledData, 128, true, true) 
	{
		memset(ledData, 0, sizeof(ledData));  // set all LEDs to black
	}

	/**
	* Creates and saves the CLEDController object for the strip, using WS2812B
	* as the strip type.
	*/
	void begin() {
		cNeoEyes::begin(FastLED.addLeds<NEOPIXEL, DataPin>(ledData, 128));
	}

  // void setExpression(CRGB expression[8][16]) {
  //   cNeoEyes::setExpression(expression);
  // }

  // void setEmote(emote expression) {
  //   // set the matrix based on the chosen existing expression... or a custom matrix
  //   switch (expression) {
  //     case neutral:
  //       cNeoEyes::setExpression(deadFace);
  //       break;
  //     case right:
  //       cNeoEyes::setExpression({
  //         // Row 1
  //         { CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black },
  //         // Row 2
  //         { CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black },
  //         // Row 3
  //         { CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black },
  //         // Row 4
  //         { CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red },
  //         // Row 5
  //         { CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red },
  //         // Row 6
  //         { CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black },
  //         // Row 7
  //         { CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black },
  //         // Row 8
  //         { CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black }
  //       });
  //       break;
  //     case left:
  //       cNeoEyes::setExpression({
  //         // Row 1
  //         { CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black },
  //         // Row 2
  //         { CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black },
  //         // Row 3
  //         { CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black },
  //         // Row 4
  //         { CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red },
  //         // Row 5
  //         { CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red },
  //         // Row 6
  //         { CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black },
  //         // Row 7
  //         { CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black },
  //         // Row 8
  //         { CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black }
  //       });
  //       break;
  //     case up:
  //       cNeoEyes::setExpression({
  //         // Row 1
  //         { CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black },
  //         // Row 2
  //         { CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black },
  //         // Row 3
  //         { CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black },
  //         // Row 4
  //         { CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red },
  //         // Row 5
  //         { CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red },
  //         // Row 6
  //         { CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black },
  //         // Row 7
  //         { CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black },
  //         // Row 8
  //         { CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black }
  //       });
  //       break;
  //     case down:
  //       cNeoEyes::setExpression({
  //         // Row 1
  //         { CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black },
  //         // Row 2
  //         { CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black },
  //         // Row 3
  //         { CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black },
  //         // Row 4
  //         { CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red },
  //         // Row 5
  //         { CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red },
  //         // Row 6
  //         { CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black },
  //         // Row 7
  //         { CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black },
  //         // Row 8
  //         { CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black }
  //       });
  //       break;
  //     case happy:
  //       cNeoEyes::setExpression({
  //         // Row 1
  //         { CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black },
  //         // Row 2
  //         { CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black },
  //         // Row 3
  //         { CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black },
  //         // Row 4
  //         { CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red },
  //         // Row 5
  //         { CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red },
  //         // Row 6
  //         { CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black },
  //         // Row 7
  //         { CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black },
  //         // Row 8
  //         { CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black }
  //       });
  //       break;
  //     case sad:
  //       cNeoEyes::setExpression({
  //         // Row 1
  //         { CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black },
  //         // Row 2
  //         { CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black },
  //         // Row 3
  //         { CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black },
  //         // Row 4
  //         { CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red },
  //         // Row 5
  //         { CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red },
  //         // Row 6
  //         { CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black },
  //         // Row 7
  //         { CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black },
  //         // Row 8
  //         { CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black }
  //       });
  //       break;
  //     case angry:
  //       cNeoEyes::setExpression({
  //         // Row 1
  //         { CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black },
  //         // Row 2
  //         { CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black },
  //         // Row 3
  //         { CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black },
  //         // Row 4
  //         { CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red },
  //         // Row 5
  //         { CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red },
  //         // Row 6
  //         { CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black },
  //         // Row 7
  //         { CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black },
  //         // Row 8
  //         { CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black }
  //       });
  //       break;
  //     case confused:
  //       cNeoEyes::setExpression({
  //         // Row 1
  //         { CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black },
  //         // Row 2
  //         { CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black },
  //         // Row 3
  //         { CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black },
  //         // Row 4
  //         { CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red },
  //         // Row 5
  //         { CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red },
  //         // Row 6
  //         { CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black },
  //         // Row 7
  //         { CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black },
  //         // Row 8
  //         { CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black }
  //       });
  //       break;
  //     case dead:
  //       cNeoEyes::setExpression({{ CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red },
  //         // Row 2
  //         { CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black },
  //         // Row 3
  //         { CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black },
  //         // Row 4
  //         { CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black },
  //         // Row 5
  //         { CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black },
  //         // Row 6
  //         { CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black },
  //         // Row 7
  //         { CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black },
  //         // Row 8
  //         { CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red }
  //       });
  //       break;
  //     default:
  //       break;
  //   }
  // }



private:
	CRGB ledData[128];
};


#endif
