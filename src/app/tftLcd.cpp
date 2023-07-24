

#include <TFT_eSPI.h> // Include the graphics library (this includes the sprite functions)
#include <lvgl.h>
#include "../src/lvglGui/ui.h"
static const uint16_t screenWidth  = 240;
static const uint16_t screenHeight = 320;
static lv_disp_draw_buf_t draw_buf;
// Pause in milliseconds to set scroll speed
#define WAIT 0
TFT_eSPI tft=TFT_eSPI();
void my_disp_flush( lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p );
void my_touchpad_read( lv_indev_drv_t * indev_driver, lv_indev_data_t * data );
void touch_calibrate();
uint16_t calData[5] = { 513, 3010, 363, 3283, 2};
extern QueueHandle_t xBinarySemaphore;
void lv_my_widgets(void);
void lcdInit()
{
    lv_indev_drv_t indev_drv;                  /*Descriptor of a input device driver*/

    TFT_eSprite img = TFT_eSprite(&tft); // Create Sprite object "img" with pointer to "tft" object
                                         //                                    // the pointer is used by pushSprite() to push it onto the TFT
    tft.init();
    tft.setRotation(0);

    tft.fillScreen(TFT_BLUE);
    //touch_calibrate();
    tft.setTouch((uint16_t *)calData);
    lv_init();

    static lv_disp_draw_buf_t draw_buf_dsc_3;
    static lv_color_t buf_3_1[screenWidth * screenHeight/6];            /*A screen sized buffer*/
    lv_disp_draw_buf_init(&draw_buf_dsc_3, buf_3_1, NULL,
                          screenWidth * screenHeight / 6);   /*Initialize the display buffer*/

    /*Initialize the display*/
    static lv_disp_drv_t disp_drv;                         /*Descriptor of a display driver*/
    lv_disp_drv_init(&disp_drv);                    /*Basic initialization*/

    /*Set up the functions to access to your display*/

    /*Set the resolution of the display*/
    disp_drv.hor_res = screenWidth;
    disp_drv.ver_res = screenHeight;

    /*Used to copy the buffer's content to the display*/
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.rotated = LV_DISP_ROT_NONE;
    /*Set a display buffer*/
    disp_drv.draw_buf = &draw_buf_dsc_3;
    /*Required for Example 3)*/
    //disp_drv.full_refresh = 1;

    /* Fill a memory array with a color if you have GPU.
     * Note that, in lv_conf.h you can enable GPUs that has built-in support in LVGL.
     * But if you have a different GPU you can use with this callback.*/
    //disp_drv.gpu_fill_cb = gpu_fill;

    /*Finally register the driver*/

    lv_indev_drv_init(&indev_drv);             /*Basic initialization*/
    lv_disp_drv_register(&disp_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;    /*Touch pad is a pointer-like device*/
    indev_drv.read_cb = my_touchpad_read;      /*Set your driver function*/
    lv_indev_drv_register(&indev_drv);         /*Finally register the driver*/
    ui_init();
    #if 0
    /* Create simple label */
    lv_obj_t *label = lv_label_create( lv_scr_act() );
    lv_label_set_text( label, LVGL_Arduino.c_str() );
    lv_obj_align( label, LV_ALIGN_CENTER, 0, 0 );
#else
    /* Try an example from the lv_examples Arduino library
       make sure to include it as written above.
    lv_example_btn_1();
   */

    // uncomment one of these demos
    // lv_demo_widgets();            // OK
    // lv_demo_benchmark();          // OK
    // lv_demo_keypad_encoder();     // works, but I haven't an encoder
    // lv_demo_music();              // NOK
    // lv_demo_printer();
    // lv_demo_stress();             // seems to be OK
#endif

}

// ICACHE_RAM_ATTR void touchIrq()
// {
//     BaseType_t xHigherPriorityTaskWoken;
//     xHigherPriorityTaskWoken = pdFALSE;
//     xSemaphoreGiveFromISR(xBinarySemaphore,&xHigherPriorityTaskWoken);
//     //touchFlag=1;
// }
void my_disp_flush( lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p )
{
    uint32_t w = ( area->x2 - area->x1 + 1 );
    uint32_t h = ( area->y2 - area->y1 + 1 );

    tft.startWrite();
    tft.setAddrWindow( area->x1, area->y1, w, h );
    tft.pushColors( ( uint16_t * )&color_p->full, w * h, true );
    tft.endWrite();

    lv_disp_flush_ready( disp );
}
void my_touchpad_read( lv_indev_drv_t * indev_driver, lv_indev_data_t * data )
{
    uint16_t touchX, touchY;

    bool touched = tft.getTouch( &touchX, &touchY, 600 );

    if( !touched )
    {
        data->state = LV_INDEV_STATE_REL;
    }
    else
    {
        data->state = LV_INDEV_STATE_PR;

        /*Set the coordinates*/
        data->point.x = touchX;
        data->point.y = touchY;
        Serial.printf("x:%d\r\n",touchX);
        Serial.printf("y:%d\r\n",touchY);
        Serial.printf("\r\n");
    }
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

  tft.calibrateTouch((uint16_t*)calData, TFT_MAGENTA, TFT_BLACK, 15);

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