// Check slash vs underscore
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks"
#include "neopixel.pio.h"


#include <vector>

#include "stdlib.h"

class NeoMatrix {
    private:
        /* data */
        uint8_t width, height;
        std::vector<uint32_t> pixel_map;
    public:
        NeoMatrix(uint8_t width, uint8_t height);
        ~NeoMatrix();
        void set_pixel(uint8_t row, uint8_t col, uint32_t color);
        bool init();
        void write();
        void clear();
};

NeoMatrix::NeoMatrix(uint8_t width, uint8_t height) {
    /* Constructor */
    this->width = width;
    this->height = height;

    pixel_map.resize(height, std::vector<uint32_t>(width, 0));
}

bool NeoMatrix::init() {
    /* Initializes the NeoMatrix */
    const uint LED_PIN = 10;

    // Set GPIO 
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, 1);
    gpio_put(LED_PIN, 1);
    
    PIO pio = pio0;
    return true;
}

void NeoMatrix::set_pixel(uint8_t row, uint8_t col, uint32_t color) {
    /* Sets the pixel at row, col to color */
    this->pixel_map[row][col] = color;
    return;
}

void NeoMatrix::write() {
    /* Writes the pixel_map to the NeoMatrix */
    for(uint8_t row = 0; row < this->height; row++) {
        for(uint8_t col = 0; col < this->width; col++) {
            // Write the pixel to the NeoMatrix
            pio_sm_put_blocking(pio, 0, this->pixel_map[row][col] << 8);
        }
    }
    return;
}

void NeoMatrix::clear() {
    /* Clears the pixel_map */
    for(uint8_t row = 0; row < this->height; row++) {
        for(uint8_t col = 0; col < this->width; col++) {
            // Clear the pixel at row, col
            this->pixel_map[row][col] = 0;
        }
    }
    return;
}