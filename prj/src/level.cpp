#include "../library/lis3dh.h"
#include "pico/stdlib.h"

int main() {
  stdio_init_all();
  // Singleton for the accelerometer
  sleep_ms(5000);
  printf("Setting up accelerometer\n");
  lis3dh accel;
  // initialize the accelerometer
  sleep_ms(5000);
  printf("Initializing accelerometer\n");
  accel.init();
  
  // Test blink
  const uint LED_PIN = 13;
  gpio_init(LED_PIN);
  gpio_set_dir(LED_PIN, GPIO_OUT);

  while (1) {
    // Update the accelerometer values
    accel.update();
    printf("X: %.3fg\n", accel.get_x());
    printf("Y: %.3fg\n", accel.get_y());
    printf("Z: %.3fg\n", accel.get_z());
    // Print the values
    printf("Test USB Serial\n");
    gpio_put(LED_PIN, 1);
    sleep_ms(50);
    gpio_put(LED_PIN, 0);
    sleep_ms(50);
  }
  return 0;
}
