

#include <TFT_eSPI.h> // Include the graphics library (this includes the sprite functions)

#define IWIDTH 240
#define IHEIGHT 30

// Pause in milliseconds to set scroll speed
#define WAIT 0
TFT_eSPI tft=TFT_eSPI();
ICACHE_RAM_ATTR void touchIrq();
void touch_calibrate();
static uint16_t calData[5];
int touchFlag=0;
extern QueueHandle_t xBinarySemaphore;
void lcdInit()
{
    TFT_eSprite img = TFT_eSprite(&tft); // Create Sprite object "img" with pointer to "tft" object
                                         //                                    // the pointer is used by pushSprite() to push it onto the TFT
    tft.init();
    tft.setRotation(1);

    tft.fillScreen(TFT_BLUE);
    touch_calibrate();
    tft.setTouch(calData);
    attachInterrupt(16,touchIrq,FALLING );
}
ICACHE_RAM_ATTR void touchIrq()
{
    BaseType_t xHigherPriorityTaskWoken;
    xHigherPriorityTaskWoken = pdFALSE;
    xSemaphoreGiveFromISR(xBinarySemaphore,&xHigherPriorityTaskWoken);
    //touchFlag=1;
}
void touch_calibrate()
{
  
  uint8_t calDataOK = 0;

  // Calibrate
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(20, 0);
  tft.setTextFont(2);
  tft.setTextSize(1);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);

  tft.println("Touch corners as indicated");

  tft.setTextFont(1);
  tft.println();

  tft.calibrateTouch(calData, TFT_MAGENTA, TFT_BLACK, 15);

  Serial.println(); Serial.println();
  Serial.println("// Use this calibration code in setup():");
  Serial.print("  uint16_t calData[5] = ");
  Serial.print("{ ");

  for (uint8_t i = 0; i < 5; i++)
  {
    Serial.print(calData[i]);
    if (i < 4) Serial.print(", ");
  }

  Serial.println(" };");
  Serial.print("  tft.setTouch(calData);");
  Serial.println(); Serial.println();

  tft.fillScreen(TFT_BLACK);
  
  tft.setTextColor(TFT_GREEN, TFT_BLACK);
  tft.println("Calibration complete!");
  tft.println("Calibration code sent to Serial port.");

  delay(4000);
}