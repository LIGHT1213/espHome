// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.1
// LVGL version: 8.3.6
// Project name: esphomeLvglGui

#include "../ui.h"

void ui_Screen2_screen_init(void)
{
    ui_Screen2 = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Screen2, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Button7 = lv_btn_create(ui_Screen2);
    lv_obj_set_width(ui_Button7, 61);
    lv_obj_set_height(ui_Button7, 24);
    lv_obj_set_x(ui_Button7, 83);
    lv_obj_set_y(ui_Button7, 142);
    lv_obj_set_align(ui_Button7, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Button7, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_Button7, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Arc4 = lv_arc_create(ui_Screen2);
    lv_obj_set_width(ui_Arc4, 150);
    lv_obj_set_height(ui_Arc4, 150);
    lv_obj_set_align(ui_Arc4, LV_ALIGN_CENTER);

    lv_obj_add_event_cb(ui_Button7, ui_event_Button7, LV_EVENT_ALL, NULL);

}
