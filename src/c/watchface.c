#include <pebble.h>

static Window *s_window;
static TextLayer *s_time_layer;

// static void prv_select_click_handler(ClickRecognizerRef recognizer, void *context) {
//   text_layer_set_text(s_text_layer, "Select");
// }

// static void prv_up_click_handler(ClickRecognizerRef recognizer, void *context) {
//   text_layer_set_text(s_text_layer, "Up");
// }

// static void prv_down_click_handler(ClickRecognizerRef recognizer, void *context) {
//   text_layer_set_text(s_text_layer, "Down");
// }

// static void prv_click_config_provider(void *context) {
//   window_single_click_subscribe(BUTTON_ID_SELECT, prv_select_click_handler);
//   window_single_click_subscribe(BUTTON_ID_UP, prv_up_click_handler);
//   window_single_click_subscribe(BUTTON_ID_DOWN, prv_down_click_handler);
// }

static void prv_window_load(Window *window) {
  // Get information about the Window
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  // Create the TextLayer with specific bounds
  s_time_layer = text_layer_create(
    GRect(0, PBL_IF_ROUND_ELSE(58, 52), bounds.size.w, 50));

  // Improve the layout to be more like a watchface
  text_layer_set_background_color(s_time_layer, GColorClear);
  text_layer_set_text_color(s_time_layer, GColorBlack);
  text_layer_set_text(s_time_layer, "00:00");
  text_layer_set_font(s_time_layer, fonts_get_system_font(FONT_KEY_BITHAM_42_BOLD));
  text_layer_set_text_alignment(s_time_layer, GTextAlignmentCenter);

  // Add it as a child layer to the Window's root layer
  layer_add_child(window_layer, text_layer_get_layer(s_time_layer));
}

static void prv_window_unload(Window *window) {
  // Destroy TextLayer
  text_layer_destroy(s_time_layer);
}

static void prv_init(void) {
  // Create main Window element and assign to pointer
  s_window = window_create();
  // window_set_click_config_provider(s_window, prv_click_config_provider);

  // Set handlers to manage the elements inside the Window
  window_set_window_handlers(s_window, (WindowHandlers) {
    .load = prv_window_load,
    .unload = prv_window_unload,
  });

  // Show the Window on the watch, with animated=true
  const bool animated = true;
  window_stack_push(s_window, animated);
}

static void prv_deinit(void) {
  // Destroy Window
  window_destroy(s_window);
}

int main(void) {
  prv_init();

  // APP_LOG(APP_LOG_LEVEL_DEBUG, "Done initializing, pushed window: %p", s_window);

  app_event_loop();
  prv_deinit();
}
