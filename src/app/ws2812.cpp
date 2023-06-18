#ifdef ENABLE_WS2812
#include <FastLED.h>
uint8_t max_bright = 127; // LED亮度控制变量，可使用数值为 0 ～ 255， 数值越大则光带亮度越高
CRGB leds[NUM_LEDS];      // 建立灯带leds
#define NUM_LEDS 64     // LED灯珠数量
#define DATA_PIN 5      // Arduino输出控制信号引脚 接LED灯环的DI
#define LED_TYPE WS2812 // LED灯环型号
#define COLOR_ORDER GRB // RGB灯珠中红色、绿色、蓝色LED的排列顺序
void ws2812Init()
{
  LEDS.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS); // 初始化灯带
  FastLED.setBrightness(max_bright);
}

#endif  