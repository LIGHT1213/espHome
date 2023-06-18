

#include <TFT_eSPI.h> // Include the graphics library (this includes the sprite functions)

#define IWIDTH 240
#define IHEIGHT 30

// Pause in milliseconds to set scroll speed
#define WAIT 0
TFT_eSPI tft=TFT_eSPI();
void lcdInit()
{

    TFT_eSprite img = TFT_eSprite(&tft); // Create Sprite object "img" with pointer to "tft" object
                                         //                                    // the pointer is used by pushSprite() to push it onto the TFT
    tft.init();
    tft.setRotation(0);

    tft.fillScreen(TFT_BLUE);
}