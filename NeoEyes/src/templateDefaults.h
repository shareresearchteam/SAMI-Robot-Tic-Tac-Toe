// Some default emotion & expression items for the pixel eyes, and the template array.
// These values should be placed in the position in the template that they would go in the visual display, rather than by pin numbering
// Easy reference colors with names from from here: https://fastled.io/docs/struct_c_r_g_b.html#aeb40a08b7cb90c1e21bd408261558b99
// You can call them via CRGB::Black or CRGB::Red
// Alternatively you can define custom values by making CRGB objects such as CRGB(0xF0F8FF) would give you the same value as CRGB::AliceBlue

// Template to use is this! Already set up to be filled in with the pre-defined colors
CRGB template[8][16] = {
  // Row 1
  { CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB:: },
  // Row 2
  { CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB:: },
  // Row 3
  { CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB:: },
  // Row 4
  { CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB:: },
  // Row 5
  { CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB:: },
  // Row 6
  { CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB:: },
  // Row 7
  { CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB:: },
  // Row 8
  { CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB:: },
};

// From what I could tell from the code, the different "expressions" that you've made that we can make into default expressions and use
// for folks to call are as below, and include some of the more "functional" ones as well
// neutral
// right
// left
// up
// down
// happy
// sad
// angry
// confused
// blink