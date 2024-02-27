#include "../library/lis3dh.h"
#include "../library/neomatrix.h"
#include "pico/stdlib.h"

int main() {
  stdio_init_all();
  // Singleton for the accelerometer
  printf("Setting up accelerometer\n");
  lis3dh accel;
  // initialize the accelerometer
  sleep_ms(5000);
  printf("Initializing accelerometer\n");
  accel.init();

  NeoMatrix neo(8, 8);
  printf("Initializing NeoMatrix\n");
  neo.init();
  
  while (1) {
    // Update the accelerometer values
    neo.clear();
    accel.update();
    printf("X: %.3fg\n", accel.get_x());
    printf("Y: %.3fg\n", accel.get_y());
    printf("Z: %.3fg\n", accel.get_z());
    // Set the pixel color based on the acceleration
    if( (accel.get_x() <= 0.1 && accel.get_x() >= -0.1) && (accel.get_y() <= 0.1 && accel.get_y() >= -0.1) && (accel.get_z() <= 1.1 && accel.get_z() >= 0.9)){
      // Set all pixels to red
      for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
          neo.set_pixel(i, j, 0xFF0000);
        }
      }
    } else {
      for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
          neo.set_pixel(i, j, 0x00FF00);
        }
      }
    }
    sleep_ms(25);
    neo.write();
  }
  return 0;
}
